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

#ifndef QACCESSIBLEOBJECT_H
#define QACCESSIBLEOBJECT_H

#include <QtGui/qaccessible.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Gui)

#ifndef QT_NO_ACCESSIBILITY

class QAccessibleObjectPrivate;
class QObject;

class Q_GUI_EXPORT QAccessibleObject : public QAccessibleInterface
{
public:
    explicit QAccessibleObject(QObject *object);

    bool isValid() const;
    QObject *object() const;

    // properties
    QRect rect(int child) const;
    void setText(Text t, int child, const QString &text);

    // actions
    int userActionCount(int child) const;
    bool doAction(int action, int child, const QVariantList &params);
    QString actionText(int action, Text t, int child) const;

protected:
    virtual ~QAccessibleObject();

private:
    friend class QAccessibleObjectEx;
    QAccessibleObjectPrivate *d;
    Q_DISABLE_COPY(QAccessibleObject)
};

class Q_GUI_EXPORT QAccessibleObjectEx : public QAccessibleInterfaceEx
{
public:
    explicit QAccessibleObjectEx(QObject *object);

    bool isValid() const;
    QObject *object() const;

    // properties
    QRect rect(int child) const;
    void setText(Text t, int child, const QString &text);

    // actions
    int userActionCount(int child) const;
    bool doAction(int action, int child, const QVariantList &params);
    QString actionText(int action, Text t, int child) const;

protected:
    virtual ~QAccessibleObjectEx();

private:
    QAccessibleObjectPrivate *d;
    Q_DISABLE_COPY(QAccessibleObjectEx)
};

class Q_GUI_EXPORT QAccessibleApplication : public QAccessibleObject
{
public:
    QAccessibleApplication();

    // relations
    int childCount() const;
    int indexOfChild(const QAccessibleInterface*) const;
    Relation relationTo(int, const QAccessibleInterface *, int) const;

    // navigation
    int childAt(int x, int y) const;
    int navigate(RelationFlag, int, QAccessibleInterface **) const;

    // properties and state
    QString text(Text t, int child) const;
    Role role(int child) const;
    State state(int child) const;

    // actions
    int userActionCount(int child) const;
    bool doAction(int action, int child, const QVariantList &params);
    QString actionText(int action, Text t, int child) const;
};

#endif // QT_NO_ACCESSIBILITY

QT_END_NAMESPACE

QT_END_HEADER

#endif // QACCESSIBLEOBJECT_H
