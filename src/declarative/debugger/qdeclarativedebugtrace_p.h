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

#ifndef QDECLARATIVEDEBUGTRACE_P_H
#define QDECLARATIVEDEBUGTRACE_P_H

#include <private/qdeclarativedebugservice_p.h>
#include <private/qperformancetimer_p.h>
#include <QtCore/qglobal.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

struct QDeclarativeDebugData
{
    qint64 time;
    int messageType;
    int detailType;

    //###
    QString detailData; //used by RangeData and RangeLocation
    int line;           //used by RangeLocation

    QByteArray toByteArray() const;
};

class QUrl;
class Q_DECLARATIVE_EXPORT QDeclarativeDebugTrace : public QDeclarativeDebugService
{
public:
    enum Message {
        Event,
        RangeStart,
        RangeData,
        RangeLocation,
        RangeEnd,
        Complete,

        MaximumMessage
    };

    enum EventType {
        FramePaint,
        Mouse,
        Key,

        MaximumEventType
    };

    enum RangeType {
        Painting,
        Compiling,
        Creating,
        Binding,            //running a binding
        HandlingSignal,     //running a signal handler

        MaximumRangeType
    };

    static void addEvent(EventType);

    static void startRange(RangeType);
    static void rangeData(RangeType, const QString &);
    static void rangeData(RangeType, const QUrl &);
    static void rangeLocation(RangeType, const QString &, int);
    static void rangeLocation(RangeType, const QUrl &, int);
    static void endRange(RangeType);

    QDeclarativeDebugTrace();
#ifdef CUSTOM_DECLARATIVE_DEBUG_TRACE_INSTANCE
public:
    static QDeclarativeDebugTrace* globalInstance();
    static void setGlobalInstance(QDeclarativeDebugTrace *custom_instance);
protected:
    virtual void messageReceived(const QByteArray &);
protected:
    virtual void addEventImpl(EventType);
    virtual void startRangeImpl(RangeType);
    virtual void rangeDataImpl(RangeType, const QString &);
    virtual void rangeDataImpl(RangeType, const QUrl &);
    virtual void rangeLocationImpl(RangeType, const QString &, int);
    virtual void rangeLocationImpl(RangeType, const QUrl &, int);
    virtual void endRangeImpl(RangeType);
#else
protected:
    virtual void messageReceived(const QByteArray &);
private:
    void addEventImpl(EventType);
    void startRangeImpl(RangeType);
    void rangeDataImpl(RangeType, const QString &);
    void rangeDataImpl(RangeType, const QUrl &);
    void rangeLocationImpl(RangeType, const QString &, int);
    void rangeLocationImpl(RangeType, const QUrl &, int);
    void endRangeImpl(RangeType);
#endif
    void processMessage(const QDeclarativeDebugData &);
    void sendMessages();
    QPerformanceTimer m_timer;
    bool m_enabled;
    bool m_deferredSend;
    bool m_messageReceived;
    QList<QDeclarativeDebugData> m_data;
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // QDECLARATIVEDEBUGTRACE_P_H

