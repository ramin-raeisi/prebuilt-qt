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
#include "qcocoawindow.h"
#include "qnswindowdelegate.h"
#include "qcocoaautoreleasepool.h"

#include <QWidget>

#include <QtGui/QApplication>

#include <QWindowSystemInterface>

#include <QDebug>

QCocoaWindow::QCocoaWindow(QWidget *tlw)
    : QPlatformWindow(tlw)
{
    QCocoaAutoReleasePool pool;
    const QRect geo = tlw->geometry();
    NSRect frame = NSMakeRect(geo.x(), geo.y(), geo.width(), geo.height());

    m_nsWindow  = [[NSWindow alloc] initWithContentRect:frame
                                            styleMask:NSTitledWindowMask|NSClosableWindowMask|NSMiniaturizableWindowMask|NSResizableWindowMask
                                            backing:NSBackingStoreBuffered
                                            defer:YES];

    QNSWindowDelegate *delegate = [[QNSWindowDelegate alloc] initWithQCocoaWindow:this];
    [m_nsWindow setDelegate:delegate];

    [m_nsWindow makeKeyAndOrderFront:nil];
    [m_nsWindow setAcceptsMouseMovedEvents:YES];
}

QCocoaWindow::~QCocoaWindow()
{
}

void QCocoaWindow::setGeometry(const QRect &rect)
{
    QPlatformWindow::setGeometry(rect);

    NSRect bounds = NSMakeRect(rect.x(), rect.y(), rect.width(), rect.height());
    [[m_nsWindow contentView]setFrameSize:bounds.size];
}

void QCocoaWindow::setVisible(bool visible)
{
    Q_UNUSED(visible);
}

WId QCocoaWindow::winId() const
{
    return WId([m_nsWindow windowNumber]);
}

NSView *QCocoaWindow::contentView() const
{
    return [m_nsWindow contentView];
}

void QCocoaWindow::setContentView(NSView *contentView)
{
    [m_nsWindow setContentView:contentView];
}

void QCocoaWindow::windowDidResize()
{
    //jlind: XXX This isn't ideal. Eventdispatcher does not run when resizing...
    NSRect rect = [[m_nsWindow contentView]frame];
    QRect geo(rect.origin.x,rect.origin.y,rect.size.width,rect.size.height);
    QWindowSystemInterface::handleGeometryChange(widget(),geo);
}
