/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the tools applications of the Qt Toolkit.
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

#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include "parser.h"
#include <QList>
#include <QSet>
#include <stdio.h>

QT_BEGIN_NAMESPACE

struct Macro
{
    Symbols symbols;
};

#ifdef USE_LEXEM_STORE
typedef QByteArray MacroName;
#else
typedef SubArray MacroName;
#endif
typedef QHash<MacroName, Macro> Macros;
typedef QVector<MacroName> MacroSafeSet;


class Preprocessor : public Parser
{
public:
    Preprocessor(){}
    static bool preprocessOnly;
    struct IncludePath
    {
        inline explicit IncludePath(const QByteArray &_path)
            : path(_path), isFrameworkPath(false) {}
        QByteArray path;
        bool isFrameworkPath;
    };
    QList<IncludePath> includes;
    QList<QByteArray> frameworks;
    QSet<QByteArray> preprocessedIncludes;
    Macros macros;
    Symbols preprocessed(const QByteArray &filename, FILE *file);


    void skipUntilEndif();
    bool skipBranch();

    void substituteMacro(const MacroName &macro, Symbols &substituted, MacroSafeSet safeset = MacroSafeSet());
    void substituteUntilNewline(Symbols &substituted, MacroSafeSet safeset = MacroSafeSet());

    int evaluateCondition();


private:
    void until(Token);

    void preprocess(const QByteArray &filename, Symbols &preprocessed);
};

QT_END_NAMESPACE

#endif // PREPROCESSOR_H
