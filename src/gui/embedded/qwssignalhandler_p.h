/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QWSSIGNALHANDLER_P_H
#define QWSSIGNALHANDLER_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of the QLibrary class.  This header file may change from
// version to version without notice, or even be removed.
//
// We mean it.
//

#include <QtCore/qglobal.h>

#ifndef QT_NO_QWS_SIGNALHANDLER

#include <QtCore/qhash.h>
#include <QtCore/qlist.h>
#include <QtCore/qobjectcleanuphandler.h>

QT_BEGIN_NAMESPACE

typedef void (*qt_sighandler_t)(int);

class QLock;
class QWSLock;

class QWSSignalHandlerPrivate;

class Q_GUI_EXPORT QWSSignalHandler
{
public:
    static QWSSignalHandler* instance();

    ~QWSSignalHandler();

#ifndef QT_NO_QWS_MULTIPROCESS
    inline void addLock(QLock *lock) { locks.append(lock); }
    inline void removeLock(QLock *lock) { locks.removeOne(lock); }
    inline void addWSLock(QWSLock *wslock) { wslocks.append(wslock); }
    inline void removeWSLock(QWSLock *wslock) { wslocks.removeOne(wslock); }
#endif
    inline void addObject(QObject *object) { (void)objects.add(object); }

private:
    QWSSignalHandler();

    void clear();

    static void handleSignal(int signal);

    QHash<int, qt_sighandler_t> oldHandlers;
#ifndef QT_NO_QWS_MULTIPROCESS
    QList<QLock *> locks;
    QList<QWSLock *> wslocks;
#endif
    QObjectCleanupHandler objects;

    friend class QWSSignalHandlerPrivate;
};

QT_END_NAMESPACE

#endif // QT_NO_QWS_SIGNALHANDLER

#endif // QWSSIGNALHANDLER_P_H
