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

#ifndef Patternist_TemplateParam_H
#define Patternist_TemplateParam_H

#include "qfunctionargument_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Carries meta data for @c xsl:with-param as encountered in
     * template callsites such as @c xsl:call-template and @c
     * xsl:apply-templates.
     *
     * WithParam is similar to FunctionArgument, but has in addition a default
     * value in the form of an Expression.
     *
     * @since 4.5
     * @ingroup Patternist_expressions
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class WithParam : public FunctionArgument
    {
    public:
        typedef QExplicitlySharedDataPointer<WithParam> Ptr;
        typedef QHash<QXmlName, Ptr> Hash;

        /**
         * @p sourceExpression can not be @c null.
         */
        inline WithParam(const QXmlName name,
                         const SequenceType::Ptr &type,
                         const Expression::Ptr &sourceExpression);

        inline void setSourceExpression(const Expression::Ptr &expr)
        {
            Q_ASSERT(expr);
            m_sourceExpression = expr;
        }

        /**
         * @short Returns the expression which is the source the value for this
         * parameter.
         *
         * Guaranteed to never be @c null.
         */
        inline Expression::Ptr sourceExpression() const
        {
            return m_sourceExpression;
        }

    private:
        Expression::Ptr m_sourceExpression;
    };

    WithParam::WithParam(const QXmlName name,
                         const SequenceType::Ptr &type,
                         const Expression::Ptr &sourceExpression) : FunctionArgument(name, type)
                                                                  , m_sourceExpression(sourceExpression)
    {
        Q_ASSERT(m_sourceExpression);
    }

}

QT_END_NAMESPACE

QT_END_HEADER

#endif
