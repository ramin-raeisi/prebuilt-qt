/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#import "config.h"
#import "ProcessLauncher.h"

#import "RunLoop.h"
#import "WebProcess.h"
#import "WebKitSystemInterface.h"
#import <crt_externs.h>
#import <mach-o/dyld.h>
#import <mach/machine.h>
#import <runtime/InitializeThreading.h>
#import <servers/bootstrap.h>
#import <spawn.h>
#import <sys/param.h>
#import <sys/stat.h>
#import <wtf/PassRefPtr.h>
#import <wtf/RetainPtr.h>
#import <wtf/Threading.h>
#import <wtf/text/CString.h>
#import <wtf/text/WTFString.h>

using namespace WebCore;

// FIXME: We should be doing this another way.
extern "C" kern_return_t bootstrap_register2(mach_port_t, name_t, mach_port_t, uint64_t);

namespace WebKit {

static void setUpTerminationNotificationHandler(pid_t pid)
{
#if HAVE(DISPATCH_H)
    dispatch_source_t processDiedSource = dispatch_source_create(DISPATCH_SOURCE_TYPE_PROC, pid, DISPATCH_PROC_EXIT, dispatch_get_current_queue());
    dispatch_source_set_event_handler(processDiedSource, ^{
        int status;
        waitpid(dispatch_source_get_handle(processDiedSource), &status, 0);
        dispatch_source_cancel(processDiedSource);
    });
    dispatch_source_set_cancel_handler(processDiedSource, ^{
        dispatch_release(processDiedSource);
    });
    dispatch_resume(processDiedSource);
#endif
}

class EnvironmentVariables {
    WTF_MAKE_NONCOPYABLE(EnvironmentVariables);

public:
    EnvironmentVariables()
        : m_environmentPointer(*_NSGetEnviron())
    {
    }

    ~EnvironmentVariables()
    {
        size_t size = m_allocatedStrings.size();
        for (size_t i = 0; i < size; ++i)
            fastFree(m_allocatedStrings[i]);
    }

    void set(const char* name, const char* value)
    {
        // Check if we need to copy the environment.
        if (m_environmentPointer == *_NSGetEnviron())
            copyEnvironmentVariables();

        // Allocate a string for the name and value.
        const char* nameAndValue = createStringForVariable(name, value);

        for (size_t i = 0; i < m_environmentVariables.size() - 1; ++i) {
            if (valueIfVariableHasName(m_environmentVariables[i], name)) {
                // Just replace the environment variable.
                m_environmentVariables[i] = const_cast<char*>(nameAndValue);
                return;
            }
        }

        // Append the new string.
        ASSERT(!m_environmentVariables.last());
        m_environmentVariables.last() = const_cast<char*>(nameAndValue);
        m_environmentVariables.append(static_cast<char*>(0));

        m_environmentPointer = m_environmentVariables.data();
    }

    const char* get(const char* name) const
    {
        for (size_t i = 0; m_environmentPointer[i]; ++i) {
            if (const char* value = valueIfVariableHasName(m_environmentPointer[i], name))
                return value;
        }
        return 0;
    }

    // Will append the value with the given separator if the environment variable already exists.
    void appendValue(const char* name, const char* value, char separator)
    {
        const char* existingValue = get(name);
        if (!existingValue) {
            set(name, value);
            return;
        }

        Vector<char, 128> newValue;
        newValue.append(existingValue, strlen(existingValue));
        newValue.append(separator);
        newValue.append(value, strlen(value) + 1);

        set(name, newValue.data());
    }

    char** environmentPointer() const { return m_environmentPointer; }

private:
    const char* valueIfVariableHasName(const char* environmentVariable, const char* name) const
    {
        // Find the environment variable name.
        const char* equalsLocation = strchr(environmentVariable, '=');
        ASSERT(equalsLocation);

        size_t nameLength = equalsLocation - environmentVariable;
        if (strlen(name) != nameLength)
            return 0;
        if (memcmp(environmentVariable, name, nameLength))
            return 0;

        return equalsLocation + 1;
    }

    const char* createStringForVariable(const char* name, const char* value)
    {
        int nameLength = strlen(name);
        int valueLength = strlen(value);

        // Allocate enough room to hold 'name=value' and the null character.
        char* string = static_cast<char*>(fastMalloc(nameLength + 1 + valueLength + 1));
        memcpy(string, name, nameLength);
        string[nameLength] = '=';
        memcpy(string + nameLength + 1, value, valueLength);
        string[nameLength + 1 + valueLength] = '\0';

        m_allocatedStrings.append(string);

        return string;
    }

    void copyEnvironmentVariables()
    {
        for (size_t i = 0; (*_NSGetEnviron())[i]; i++)
            m_environmentVariables.append((*_NSGetEnviron())[i]);

        // Null-terminate the array.
        m_environmentVariables.append(static_cast<char*>(0));

        // Update the environment pointer.
        m_environmentPointer = m_environmentVariables.data();
    }

    char** m_environmentPointer;
    Vector<char*> m_environmentVariables;

    // These allocated strings will be freed in the destructor.
    Vector<char*> m_allocatedStrings;
};

void ProcessLauncher::launchProcess()
{
    // Create the listening port.
    mach_port_t listeningPort;
    mach_port_allocate(mach_task_self(), MACH_PORT_RIGHT_RECEIVE, &listeningPort);
    
    // Insert a send right so we can send to it.
    mach_port_insert_right(mach_task_self(), listeningPort, listeningPort, MACH_MSG_TYPE_MAKE_SEND);

    NSBundle *webKit2Bundle = [NSBundle bundleWithIdentifier:@"com.apple.WebKit2"];
    NSString *frameworksPath = [[webKit2Bundle bundlePath] stringByDeletingLastPathComponent];
    const char* frameworkExecutablePath = [[webKit2Bundle executablePath] fileSystemRepresentation];

    NSString *processPath;
    if (m_launchOptions.processType == ProcessLauncher::PluginProcess)
        processPath = [webKit2Bundle pathForAuxiliaryExecutable:@"PluginProcess.app"];
    else
        processPath = [webKit2Bundle pathForAuxiliaryExecutable:@"WebProcess.app"];

    NSString *processAppExecutablePath = [[NSBundle bundleWithPath:processPath] executablePath];

    RetainPtr<CFStringRef> cfLocalization(AdoptCF, WKCopyCFLocalizationPreferredName(NULL));
    CString localization = String(cfLocalization.get()).utf8();
    
    // Make a unique, per pid, per process launcher web process service name.
    CString serviceName = String::format("com.apple.WebKit.WebProcess-%d-%p", getpid(), this).utf8();

    const char* args[] = { [processAppExecutablePath fileSystemRepresentation], frameworkExecutablePath, "-type", processTypeAsString(m_launchOptions.processType), "-servicename", serviceName.data(), "-localization", localization.data(), 0 };

    // Register ourselves.
    kern_return_t kr = bootstrap_register2(bootstrap_port, const_cast<char*>(serviceName.data()), listeningPort, 0);
    ASSERT_UNUSED(kr, kr == KERN_SUCCESS);

    posix_spawnattr_t attr;
    posix_spawnattr_init(&attr);

    short flags = 0;

    // We want our process to receive all signals.
    sigset_t signalMaskSet;
    sigemptyset(&signalMaskSet);

    posix_spawnattr_setsigmask(&attr, &signalMaskSet);
    flags |= POSIX_SPAWN_SETSIGMASK;

    // Determine the architecture to use.
    cpu_type_t architecture = m_launchOptions.architecture;
    if (architecture == LaunchOptions::MatchCurrentArchitecture)
        architecture = _NSGetMachExecuteHeader()->cputype;

    cpu_type_t cpuTypes[] = { architecture };    
    size_t outCount = 0;
    posix_spawnattr_setbinpref_np(&attr, 1, cpuTypes, &outCount);

    // Start suspended so we can set up the termination notification handler.
    flags |= POSIX_SPAWN_START_SUSPENDED;

#ifndef BUILDING_ON_SNOW_LEOPARD
    static const int allowExecutableHeapFlag = 0x2000;
    if (m_launchOptions.executableHeap)
        flags |= allowExecutableHeapFlag;
#endif

    posix_spawnattr_setflags(&attr, flags);

    pid_t processIdentifier;

    EnvironmentVariables environmentVariables;

    // To make engineering builds work, if the path is outside of /System set up
    // DYLD_FRAMEWORK_PATH to pick up other frameworks, but don't do it for the
    // production configuration because it involves extra file system access.
    if (![frameworksPath hasPrefix:@"/System/"])
        environmentVariables.appendValue("DYLD_FRAMEWORK_PATH", [frameworksPath fileSystemRepresentation], ':');

    if (m_launchOptions.processType == ProcessLauncher::PluginProcess) {
        // We need to insert the plug-in process shim.
        NSString *pluginProcessShimPathNSString = [[processAppExecutablePath stringByDeletingLastPathComponent] stringByAppendingPathComponent:@"PluginProcessShim.dylib"];
        const char* pluginProcessShimPath = [pluginProcessShimPathNSString fileSystemRepresentation];

        // Make sure that the file exists.
        struct stat statBuf;
        if (stat(pluginProcessShimPath, &statBuf) == 0 && (statBuf.st_mode & S_IFMT) == S_IFREG)
            environmentVariables.appendValue("DYLD_INSERT_LIBRARIES", pluginProcessShimPath, ':');
    }
    
    int result = posix_spawn(&processIdentifier, args[0], 0, &attr, const_cast<char**>(args), environmentVariables.environmentPointer());

    posix_spawnattr_destroy(&attr);

    if (!result) {
        // Set up the termination notification handler and then ask the child process to continue.
        setUpTerminationNotificationHandler(processIdentifier);
        kill(processIdentifier, SIGCONT);
    } else {
        // We failed to launch. Release the send right.
        mach_port_deallocate(mach_task_self(), listeningPort);

        // And the receive right.
        mach_port_mod_refs(mach_task_self(), listeningPort, MACH_PORT_RIGHT_RECEIVE, -1);
        
        listeningPort = MACH_PORT_NULL;
        processIdentifier = 0;
    }
    
    // We've finished launching the process, message back to the main run loop.
    RunLoop::main()->scheduleWork(WorkItem::create(this, &ProcessLauncher::didFinishLaunchingProcess, processIdentifier, listeningPort));
}

void ProcessLauncher::terminateProcess()
{    
    if (!m_processIdentifier)
        return;
    
    kill(m_processIdentifier, SIGKILL);
}
    
void ProcessLauncher::platformInvalidate()
{
}

} // namespace WebKit
