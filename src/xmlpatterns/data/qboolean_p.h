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

#ifndef Patternist_Boolean_H
#define Patternist_Boolean_H

#include "qitem_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Implements the value instance of the @c xs:boolean type.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     * @ingroup Patternist_xdm
     */
    class Q_AUTOTEST_EXPORT Boolean : public AtomicValue
    {
    public:
        typedef AtomicValue::Ptr Ptr;

        /**
         * @returns the boolean value this Boolean represents
         */
        static bool evaluateEBV(const Item::Iterator::Ptr &e,
                                const QExplicitlySharedDataPointer<DynamicContext> &);

        static bool evaluateEBV(const Item &first,
                                const Item::Iterator::Ptr &e,
                                const QExplicitlySharedDataPointer<DynamicContext> &);

        static bool evaluateEBV(const Item &item,
                                const QExplicitlySharedDataPointer<DynamicContext> &context);

        virtual QString stringValue() const;

        /**
         * @returns a Boolean object instantiating @p value. Use True() or False()
         * if you already know what value you need.
         */
        static Boolean::Ptr fromValue(const bool value);

        /**
         * Creates a boolean value from a lexical representation. "true" and "1"
         * becomes @c true, while "false" and "0" becomes @c false.
         */
        static AtomicValue::Ptr fromLexical(const QString &val);

        /**
         * Get the Effective %Boolean Value of this boolean value. For <tt>xs:boolean</tt>, this
         * is simply the value.
         */
        virtual bool evaluateEBV(const QExplicitlySharedDataPointer<DynamicContext> &) const;

        virtual ItemType::Ptr type() const;

        inline bool value() const
        {
            return m_value;
        }

    protected:
        friend class CommonValues;
        Boolean(const bool value);

    private:
        const bool m_value;
    };
}

QT_END_NAMESPACE
QT_END_HEADER

#endif
