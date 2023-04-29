/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtXmlPatterns module of the Qt Toolkit.
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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.

#ifndef Patternist_UserFunction_H
#define Patternist_UserFunction_H

template<typename T> class QList;

#include <QSharedData>

#include "qexpression_p.h"
#include "qfunctionsignature_p.h"
#include "qvariabledeclaration_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short A function created with XQuery's <tt>declare function</tt> declaration.
     *
     * @see UserFunctionCall
     * @see ArgumentReference
     * @author Frans Englich <frans.englich@nokia.com>
     * @ingroup Patternist_expressions
     */
    class UserFunction : public QSharedData
    {
    public:
        typedef QExplicitlySharedDataPointer<UserFunction> Ptr;
        typedef QList<UserFunction::Ptr> List;

        /**
         * If @p slotOffset is -1, it means this function has no arguments.
         */
        UserFunction(const FunctionSignature::Ptr &signature,
                     const Expression::Ptr &body,
                     const VariableSlotID slotOffset,
                     const VariableDeclaration::List &varDecls);

        inline const Expression::Ptr &body() const;
        inline void setBody(const Expression::Ptr &newBody);
        inline FunctionSignature::Ptr signature() const;
        inline VariableSlotID expressionSlotOffset() const;
        inline VariableDeclaration::List argumentDeclarations() const;

    private:
        const FunctionSignature::Ptr    m_signature;
        Expression::Ptr                 m_body;
        const VariableSlotID            m_slotOffset;
        const VariableDeclaration::List m_argumentDeclarations;
    };

    inline const Expression::Ptr &UserFunction::body() const
    {
        return m_body;
    }

    inline FunctionSignature::Ptr UserFunction::signature() const
    {
        return m_signature;
    }

    inline VariableSlotID UserFunction::expressionSlotOffset() const
    {
        return m_slotOffset;
    }

    inline VariableDeclaration::List UserFunction::argumentDeclarations() const
    {
        return m_argumentDeclarations;
    }

    void UserFunction::setBody(const Expression::Ptr &newBody)
    {
        m_body = newBody;
    }

}

QT_END_NAMESPACE

QT_END_HEADER

#endif
