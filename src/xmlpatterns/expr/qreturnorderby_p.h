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

#ifndef Patternist_ReturnOrderBy_H
#define Patternist_ReturnOrderBy_H

#include "qorderby_p.h"
#include "qunlimitedcontainer_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Together with OrderBy, it implements XQuery 1.0's <tt>order by</tt> expression.
     *
     * ReturnOrderBy evaluates the sort keys and values, and hands it over to
     * OrderBy, which is an AST ancestor, using SortTuples.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     * @ingroup Patternist_expressions
     */
    class ReturnOrderBy : public UnlimitedContainer
    {
    public:
        /**
         * In @p operands the first item is the return expression, and the
         * rest, which is at least one, are the sort keys.
         */
        ReturnOrderBy(const OrderBy::Stability stability,
                      const OrderBy::OrderSpec::Vector &oSpecs,
                      const Expression::List &operands);

        virtual Item evaluateSingleton(const DynamicContext::Ptr &context) const;
        virtual bool evaluateEBV(const DynamicContext::Ptr &context) const;
        virtual SequenceType::Ptr staticType() const;
        virtual SequenceType::List expectedOperandTypes() const;
        virtual Expression::Ptr compress(const StaticContext::Ptr &context);
        virtual ExpressionVisitorResult::Ptr accept(const ExpressionVisitor::Ptr &visitor) const;
        virtual ID id() const;

        inline OrderBy::OrderSpec::Vector orderSpecs() const
        {
            return m_orderSpecs;
        }

        inline OrderBy::Stability stability() const
        {
            return m_stability;
        }

        /**
         * In the case of that we don't have a for-expression beloning us, but
         * only a let clause, this ReturnOrderBy breaks if it stays in the AST.
         * So, by default we assume that we should write ourselves away, unless
         * this function is called. The associated ForClause will call it
         * during typeCheck(), if it exists.
         */
        inline void setStay(const bool a)
        {
            m_flyAway = !a;
        }

        virtual Properties properties() const;
    private:
        /**
         * This variable is unfortunately only used at compile time. However,
         * it's tricky to get rid of it due to how QueryTransformParser would
         * have to be adapted.
         */
        const OrderBy::Stability    m_stability;

        OrderBy::OrderSpec::Vector  m_orderSpecs;

        /**
         * @see stay()
         */
        bool                        m_flyAway;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
