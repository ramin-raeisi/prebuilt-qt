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

#ifndef QLINUXINPUT_H
#define QLINUXINPUT_H

#include <qobject.h>
#include <Qt>
#include <termios.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class QSocketNotifier;

class QLinuxInputMouseHandlerData;

class QLinuxInputMouseHandler : public QObject
{
    Q_OBJECT
public:
    QLinuxInputMouseHandler(const QString &key, const QString &specification);
    ~QLinuxInputMouseHandler();

private slots:
    void readMouseData();

private:
    void sendMouseEvent(int x, int y, Qt::MouseButtons buttons);
    QSocketNotifier *          m_notify;
    int                        m_fd;
    int                        m_x, m_y;
    int m_prevx, m_prevy;
    int m_xoffset, m_yoffset;
    int m_smoothx, m_smoothy;
    Qt::MouseButtons           m_buttons;
    bool m_compression;
    bool m_smooth;
    int m_jitterLimitSquared;
    QLinuxInputMouseHandlerData *d;
};


class QWSLinuxInputKeyboardHandler;

class QLinuxInputKeyboardHandler : public QObject
{
    Q_OBJECT
public:
    QLinuxInputKeyboardHandler(const QString &key, const QString &specification);
    ~QLinuxInputKeyboardHandler();


private:
    void switchLed(int, bool);

private slots:
    void readKeycode();

private:
    QWSLinuxInputKeyboardHandler *m_handler;
    int                           m_fd;
    int                           m_tty_fd;
    struct termios                m_tty_attr;
    int                           m_orig_kbmode;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QLINUXINPUT_H
