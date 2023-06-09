/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the XMLPatterns module of the Qt Toolkit.
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

#ifndef Patternist_ColorOutput_h
#define Patternist_ColorOutput_h

#include <QtCore/QtGlobal>
#include <QtCore/QHash>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

namespace QPatternist
{
    class ColorOutputPrivate;

    class ColorOutput
    {
        enum
        {
            ForegroundShift = 10,
            BackgroundShift = 20,
            SpecialShift    = 20,
            ForegroundMask  = ((1 << ForegroundShift) - 1) << ForegroundShift,
            BackgroundMask  = ((1 << BackgroundShift) - 1) << BackgroundShift
        };

    public:
        enum ColorCodeComponent
        {
            BlackForeground         = 1 << ForegroundShift,
            BlueForeground          = 2 << ForegroundShift,
            GreenForeground         = 3 << ForegroundShift,
            CyanForeground          = 4 << ForegroundShift,
            RedForeground           = 5 << ForegroundShift,
            PurpleForeground        = 6 << ForegroundShift,
            BrownForeground         = 7 << ForegroundShift,
            LightGrayForeground     = 8 << ForegroundShift,
            DarkGrayForeground      = 9 << ForegroundShift,
            LightBlueForeground     = 10 << ForegroundShift,
            LightGreenForeground    = 11 << ForegroundShift,
            LightCyanForeground     = 12 << ForegroundShift,
            LightRedForeground      = 13 << ForegroundShift,
            LightPurpleForeground   = 14 << ForegroundShift,
            YellowForeground        = 15 << ForegroundShift,
            WhiteForeground         = 16 << ForegroundShift,

            BlackBackground         = 1 << BackgroundShift,
            BlueBackground          = 2 << BackgroundShift,
            GreenBackground         = 3 << BackgroundShift,
            CyanBackground          = 4 << BackgroundShift,
            RedBackground           = 5 << BackgroundShift,
            PurpleBackground        = 6 << BackgroundShift,
            BrownBackground         = 7 << BackgroundShift,
            DefaultColor            = 1 << SpecialShift
        };

        typedef QFlags<ColorCodeComponent> ColorCode;
        typedef QHash<int, ColorCode> ColorMapping;

        ColorOutput();
        ~ColorOutput();

        void setColorMapping(const ColorMapping &cMapping);
        ColorMapping colorMapping() const;
        void insertMapping(int colorID, const ColorCode colorCode);

        void writeUncolored(const QString &message);
        void write(const QString &message, int color = -1);
        QString colorify(const QString &message, int color = -1) const;

    private:
        ColorOutputPrivate *d;
        Q_DISABLE_COPY(ColorOutput)
    };
}

Q_DECLARE_OPERATORS_FOR_FLAGS(QPatternist::ColorOutput::ColorCode)

QT_END_NAMESPACE

QT_END_HEADER

#endif
