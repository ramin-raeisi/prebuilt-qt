/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QGRAPHICSSYSTEM_OPENKODE_H
#define QGRAPHICSSYSTEM_OPENKODE_H

#include "qopenkodeeventloopintegration.h"

#include <QtCore/qsemaphore.h>

#include <QtGui/QPlatformIntegration>
#include <QtGui/QPlatformScreen>
#include <QtGui/QPlatformGLContext>
#include <QtGui/QPlatformFontDatabase>

#include <GLES2/gl2.h>
#include <EGL/egl.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

struct KDDesktopNV;
struct KDDisplayNV;
class QOpenKODECursor;

class QOpenKODEScreen : public QPlatformScreen
{
    Q_OBJECT
public:
    QOpenKODEScreen(KDDisplayNV *kdDisplay,  KDDesktopNV *kdDesktop);
    ~QOpenKODEScreen() {}

    QRect geometry() const { return mGeometry; }
    int depth() const { return mDepth; }
    QImage::Format format() const { return mFormat; }

    EGLDisplay eglDisplay() { return mEglDisplay; }

    bool isFullScreen() const {return mIsFullScreen;}
    void setFullScreen(bool fullscreen) { mIsFullScreen = fullscreen; }
private:
    QRect mGeometry;
    int mDepth;
    QImage::Format mFormat;
    EGLDisplay mEglDisplay;
    bool mIsFullScreen;
};

class QOpenKODEIntegration : public QPlatformIntegration
{
public:
    QOpenKODEIntegration();
    ~QOpenKODEIntegration();

    bool hasCapability(QPlatformIntegration::Capability cap) const;

    QPixmapData *createPixmapData(QPixmapData::PixelType type) const;
    QPlatformWindow *createPlatformWindow(QWidget *widget, WId winId = 0) const;
    QWindowSurface *createWindowSurface(QWidget *widget, WId winId) const;

    QPlatformEventLoopIntegration *createEventLoopIntegration() const;

    QPlatformFontDatabase *fontDatabase() const;

    virtual QList<QPlatformScreen *> screens() const { return mScreens; }

    static GLuint blitterProgram();

    void setMainGLContext(QEGLPlatformContext *ctx) { mMainGlContext = ctx; }
    void mainGLContext() const { return mMainGlContext; }

private:
    QList<QPlatformScreen *> mScreens;
    QOpenKODEEventLoopIntegration *mEventLoopIntegration;
    QPlatformFontDatabase *mFontDb;
    QEGLPlatformContext *mMainGlContext;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif
