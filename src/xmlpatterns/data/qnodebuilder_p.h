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

#ifndef Patternist_NodeBuilder_H
#define Patternist_NodeBuilder_H

#include "qitem_p.h"
#include "qabstractxmlreceiver.h"
#include "qautoptr_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short Receives QAbstractXmlReceiver events and builds a node tree
     * in memory that afterwards can be retrieved via builtNode()
     *
     * @ingroup Patternist_xdm
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class NodeBuilder : public QAbstractXmlReceiver
    {
    public:
        typedef AutoPtr<NodeBuilder> Ptr;

        inline NodeBuilder()
        {
        }

        /**
         * @short Returns the document that has been built.
         *
         * If this function is called before any events have been received, the result is undefined.
         *
         * The top node that was constructed can be retrieved by calling
         * NodeModel::root() on the returned NodeModel.
         *
         * This function is not @c const, because some implementations delay
         * the node construction until the node is needed. Also, text nodes are
         * difficult, at best, to construct until one knows that all text content
         * has been received(which a call to this function in a natural way
         * signals).
         */
        virtual QAbstractXmlNodeModel::Ptr builtDocument() = 0;

        /**
         * @short Creates a copy of this NodeBuilder, that operates independently of
         * this NodeBuilder.
         *
         * The caller owns the returned instance.
         */
        virtual NodeBuilder::Ptr create(const QUrl &baseURI) const = 0;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
