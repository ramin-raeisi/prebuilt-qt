/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt3Support module of the Qt Toolkit.
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

#ifndef Q3POPUPMENU_H
#define Q3POPUPMENU_H

#include <QtGui/qmenu.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Qt3SupportLight)

class Q_COMPAT_EXPORT Q3PopupMenu : public QMenu
{
    Q_OBJECT
public:
    inline Q3PopupMenu(QWidget *parent = 0, const char *name = 0) : QMenu(parent)
    { setObjectName(QLatin1String(name)); }

    inline int exec() { return findIdForAction(QMenu::exec()); }
    inline int exec(const QPoint & pos, int indexAtPoint = 0) {
        return findIdForAction(QMenu::exec(pos, actions().value(indexAtPoint)));
    }

    void setFrameRect(QRect) {}
    QRect frameRect() const { return QRect(); }
    enum DummyFrame { Box, Sunken, Plain, Raised, MShadow, NoFrame, Panel, StyledPanel,
                      HLine, VLine, GroupBoxPanel, WinPanel, ToolBarPanel, MenuBarPanel,
                      PopupPanel, LineEditPanel, TabWidgetPanel, MShape };
    void setFrameShadow(DummyFrame) {}
    DummyFrame frameShadow() const { return Plain; }
    void setFrameShape(DummyFrame) {}
    DummyFrame frameShape() const { return NoFrame; }
    void setFrameStyle(int) {}
    int frameStyle() const  { return 0; }
    int frameWidth() const { return 0; }
    void setLineWidth(int) {}
    int lineWidth() const { return 0; }
    void setMargin(int margin) { setContentsMargins(margin, margin, margin, margin); }
    int margin() const
    { int margin; int dummy; getContentsMargins(&margin, &dummy, &dummy, &dummy);  return margin; }
    void setMidLineWidth(int) {}
    int midLineWidth() const { return 0; }

private:
    Q_DISABLE_COPY(Q3PopupMenu)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QPOPUPMENU_H
