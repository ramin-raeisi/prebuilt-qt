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

#ifndef QOPENKODEWINDOW_H
#define QOPENKODEWINDOW_H

#include <QtGui/QPlatformWindow>
#include <QtCore/QVector>

#include <KD/kd.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QEGLPlatformContext;
class QPlatformEventLoopIntegration;

class QOpenKODEWindow : public QPlatformWindow
{
public:
    QOpenKODEWindow(QWidget *tlw);
    ~QOpenKODEWindow();

    void setGeometry(const QRect &rect);
    void setVisible(bool visible);
    WId winId() const;

    QPlatformGLContext *glContext() const;

    void raise();
    void lower();

    void processKeyEvents( const KDEvent *event );
    void processMouseEvents( const KDEvent *event );

private:
    struct KDWindow *m_kdWindow;
    EGLNativeWindowType m_eglWindow;
    EGLConfig m_eglConfig;
    QVector<EGLint> m_eglWindowAttrs;
    QVector<EGLint> m_eglContextAttrs;
    EGLenum m_eglApi;
    QEGLPlatformContext *m_platformGlContext;

    bool isFullScreen;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif //QOPENKODEWINDOW_H
