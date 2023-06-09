/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef EIKSOFTKEYIMAGE_H
#define EIKSOFTKEYIMAGE_H

// FORWARD DECLARATIONS
class CEikButtonGroupContainer;

// CLASS DECLARATION

/**
*  Changes cba button's label to image.
*
*  @lib EIKCOCTL
*  @since 2.0
*/
class EikSoftkeyImage
    {
    public:

        /**
        * Set image to cba button by replacing label
        * @since 2.0
        * @param aButtonGroupContainer Button container
        * @param aImage Image to button,
        *               Takes Images ownership
        * @param aLeft  Boolean: left or right button.
        *                        If true, then change left,
        *                        if false, change right
        */
        IMPORT_C static void SetImage(CEikButtonGroupContainer* aButtonGroupContainer, CEikImage& aImage, TBool aLeft);

        /**
        * Change to cba button image back to label
        * @since 2.0
        * @param aButtonGroupContainer Button container
        * @param aLeft Boolean: left or right button.
        *                        If true, then change left,
        *                        if false, change right
        */
        IMPORT_C static void SetLabel(CEikButtonGroupContainer* aButtonGroupContainer, TBool aLeft);

    private:

        /**
        * C++ default constructor.
        */
        EikSoftkeyImage() {};


    };

#endif      // EIKSOFTKEYIMAGE_H

// End of File

