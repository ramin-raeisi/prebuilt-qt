/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QPROPERTYANIMATION_P_H
#define QPROPERTYANIMATION_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of QIODevice. This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "qpropertyanimation.h"

#include "private/qvariantanimation_p.h"

#ifndef QT_NO_ANIMATION

QT_BEGIN_NAMESPACE

class QPropertyAnimationPrivate : public QVariantAnimationPrivate
{
   Q_DECLARE_PUBLIC(QPropertyAnimation)
public:
    QPropertyAnimationPrivate()
        : targetValue(0), propertyType(0), propertyIndex(-1)
    {
    }

    QWeakPointer<QObject> target;
    //we use targetValue to be able to unregister the target from the global hash
    QObject *targetValue;

    //for the QProperty
    int propertyType;
    int propertyIndex;

    QByteArray propertyName;
    void updateProperty(const QVariant &);
    void updateMetaProperty();
};

QT_END_NAMESPACE

#endif //QT_NO_ANIMATION

#endif //QPROPERTYANIMATION_P_H
