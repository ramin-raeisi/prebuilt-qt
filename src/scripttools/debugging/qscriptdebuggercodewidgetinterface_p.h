/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtSCriptTools module of the Qt Toolkit.
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

#ifndef QSCRIPTDEBUGGERCODEWIDGETINTERFACE_P_H
#define QSCRIPTDEBUGGERCODEWIDGETINTERFACE_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/qwidget.h>

QT_BEGIN_NAMESPACE

class QScriptDebuggerScriptsModel;
class QScriptBreakpointsModel;
class QScriptToolTipProviderInterface;

class QScriptDebuggerCodeViewInterface;

class QScriptDebuggerCodeWidgetInterfacePrivate;
class Q_AUTOTEST_EXPORT QScriptDebuggerCodeWidgetInterface:
    public QWidget
{
    Q_OBJECT
public:
    ~QScriptDebuggerCodeWidgetInterface();

    virtual QScriptDebuggerScriptsModel *scriptsModel() const = 0;
    virtual void setScriptsModel(QScriptDebuggerScriptsModel *model) = 0;

    virtual QScriptBreakpointsModel *breakpointsModel() const = 0;
    virtual void setBreakpointsModel(QScriptBreakpointsModel *model) = 0;

    virtual void setToolTipProvider(QScriptToolTipProviderInterface *toolTipProvider) = 0;

    virtual qint64 currentScriptId() const = 0;
    virtual void setCurrentScript(qint64 scriptId) = 0;

    virtual void invalidateExecutionLineNumbers() = 0;

    virtual QScriptDebuggerCodeViewInterface *currentView() const = 0;

protected:
    QScriptDebuggerCodeWidgetInterface(
        QScriptDebuggerCodeWidgetInterfacePrivate &dd,
        QWidget *parent, Qt::WindowFlags flags);

private:
    Q_DECLARE_PRIVATE(QScriptDebuggerCodeWidgetInterface)
    Q_DISABLE_COPY(QScriptDebuggerCodeWidgetInterface)
};

QT_END_NAMESPACE

#endif
