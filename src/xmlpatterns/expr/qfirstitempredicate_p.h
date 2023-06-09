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

#ifndef Patternist_FirstItemPredicate_H
#define Patternist_FirstItemPredicate_H

#include "qsinglecontainer_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short A predicate that always selects the first item from its sequence.
     *
     * FirstItemPredicate corresponds exactly to the predicate
     * in the expression <tt>input[1]</tt>.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     * @ingroup Patternist_expressions
     */
    class FirstItemPredicate : public SingleContainer
    {
    public:
        /**
         * Creates a FirstItemPredicate that filters @p source.
         */
        FirstItemPredicate(const Expression::Ptr &source);

        /**
         * @returns the first item, if any, from evaluating the source expression.
         */
        virtual Item evaluateSingleton(const DynamicContext::Ptr &) const;

        /**
         * @returns a list containing one CommonSequenceTypes::ZeroOrMoreItems instance.
         */
        virtual SequenceType::List expectedOperandTypes() const;

        /**
         * @returns a SequenceType where the item type is the same as the source expression
         * and where the cardinality is either Cardinality::zeroOrOne() or Cardinality::exactlyOne(),
         * depending on the source expression.
         */
        virtual SequenceType::Ptr staticType() const;
        virtual ExpressionVisitorResult::Ptr accept(const ExpressionVisitor::Ptr &visitor) const;

        /**
         * Rewrites <tt>expression[1][1]</tt> into <tt>expression[1]</tt>.
         */
        virtual Expression::Ptr compress(const StaticContext::Ptr &context);

        /**
         * @returns always IDFirstItemPredicate.
         */
        virtual ID id() const;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
