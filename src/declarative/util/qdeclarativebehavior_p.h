/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtDeclarative module of the Qt Toolkit.
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

#ifndef QDECLARATIVEBEHAVIOR_H
#define QDECLARATIVEBEHAVIOR_H

#include "private/qdeclarativestate_p.h"

#include <qdeclarativepropertyvaluesource.h>
#include <qdeclarativepropertyvalueinterceptor.h>
#include <qdeclarative.h>
#include <QtCore/QAbstractAnimation>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Declarative)

class QDeclarativeAbstractAnimation;
class QDeclarativeBehaviorPrivate;
class Q_DECLARATIVE_PRIVATE_EXPORT QDeclarativeBehavior : public QObject, public QDeclarativePropertyValueInterceptor
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QDeclarativeBehavior)

    Q_INTERFACES(QDeclarativePropertyValueInterceptor)
    Q_CLASSINFO("DefaultProperty", "animation")
    Q_PROPERTY(QDeclarativeAbstractAnimation *animation READ animation WRITE setAnimation)
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_CLASSINFO("DeferredPropertyNames", "animation")

public:
    QDeclarativeBehavior(QObject *parent=0);
    ~QDeclarativeBehavior();

    virtual void setTarget(const QDeclarativeProperty &);
    virtual void write(const QVariant &value);

    QDeclarativeAbstractAnimation *animation();
    void setAnimation(QDeclarativeAbstractAnimation *);

    bool enabled() const;
    void setEnabled(bool enabled);

Q_SIGNALS:
    void enabledChanged();

private Q_SLOTS:
    void componentFinalized();
    void qtAnimationStateChanged(QAbstractAnimation::State,QAbstractAnimation::State);
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QDeclarativeBehavior)

QT_END_HEADER

#endif // QDECLARATIVEBEHAVIOR_H
