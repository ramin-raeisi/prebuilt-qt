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

#ifndef Patternist_GenericDynamicContext_H
#define Patternist_GenericDynamicContext_H

#include <QDateTime>
#include <QVector>

#include "qdaytimeduration_p.h"
#include "qstackcontextbase_p.h"
#include "qexpression_p.h"

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    /**
     * @short A DynamicContext supplying basic information that always is used.
     *
     * This DynamicContext is the first DynamicContext used during
     * a run and is always used. In addition, more contexts, such as
     * a Focus can be created.
     *
     * @author Frans Englich <frans.englich@nokia.com>
     */
    class GenericDynamicContext : public StackContextBase<DynamicContext>
    {
    public:
        typedef QExplicitlySharedDataPointer<GenericDynamicContext> Ptr;

        GenericDynamicContext(const NamePool::Ptr &np,
                              QAbstractMessageHandler *const messageHandler,
                              const LocationHash &locations);

        virtual xsInteger contextPosition() const;
        /**
         * @returns always @c null, the focus is always undefined when an GenericDynamicContext
         * is used.
         */
        virtual Item contextItem() const;
        virtual xsInteger contextSize();

        virtual void setFocusIterator(const Item::Iterator::Ptr &it);
        virtual Item::Iterator::Ptr focusIterator() const;

        virtual QAbstractMessageHandler * messageHandler() const;
        virtual QExplicitlySharedDataPointer<DayTimeDuration> implicitTimezone() const;
        virtual QDateTime currentDateTime() const;

        virtual QAbstractXmlReceiver *outputReceiver() const;
        void setOutputReceiver(QAbstractXmlReceiver *const receiver);

        virtual NodeBuilder::Ptr nodeBuilder(const QUrl &baseURI) const;
        void setNodeBuilder(NodeBuilder::Ptr &builder);

        virtual ResourceLoader::Ptr resourceLoader() const;
        void setResourceLoader(const ResourceLoader::Ptr &loader);

        virtual ExternalVariableLoader::Ptr externalVariableLoader() const;
        void setExternalVariableLoader(const ExternalVariableLoader::Ptr &loader);
        virtual NamePool::Ptr namePool() const;
        virtual QSourceLocation locationFor(const SourceLocationReflection *const reflection) const;
        virtual void addNodeModel(const QAbstractXmlNodeModel::Ptr &nm);
        virtual const QAbstractUriResolver *uriResolver() const;
        virtual ItemCacheCell &globalItemCacheCell(const VariableSlotID slot);
        virtual ItemSequenceCacheCell::Vector &globalItemSequenceCacheCells(const VariableSlotID slot);

        void setUriResolver(const QAbstractUriResolver *const resolver);

        /**
         * We return a null item, we have no focus.
         */
        virtual Item currentItem() const;

        /**
         * @short Returns always @c null, since we're always
         * a top-level context.
         */
        virtual DynamicContext::Ptr previousContext() const;

        virtual QExplicitlySharedDataPointer<TemplateMode> currentTemplateMode() const;

    private:
        QAbstractMessageHandler *       m_messageHandler;
        const QDateTime                 m_currentDateTime;
        const DayTimeDuration::Ptr      m_zoneOffset;
        QAbstractXmlReceiver *          m_outputReceiver;
        mutable NodeBuilder::Ptr        m_nodeBuilder;
        ExternalVariableLoader::Ptr     m_externalVariableLoader;
        ResourceLoader::Ptr             m_resourceLoader;
        NamePool::Ptr                   m_namePool;
        const LocationHash              m_locations;
        QAbstractXmlNodeModel::List     m_nodeModels;
        const QAbstractUriResolver *    m_uriResolver;
        ItemCacheCell::Vector           m_globalItemCacheCells;
        ItemSequenceCacheCell::Vector   m_globalItemSequenceCacheCells;
    };
}

QT_END_NAMESPACE

QT_END_HEADER

#endif
