/****************************************************************************
**
** Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com, author Volker Krause <volker.krause@kdab.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:COMM$
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** $QT_END_LICENSE$
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
**
******************************************************************************/

#include "qhooks_p.h"

QT_BEGIN_NAMESPACE

// Only add to the end, and bump version if you do.
quintptr Q_CORE_EXPORT qtHookData[] = {
    3, // hook data version
    QHooks::LastHookIndex, // size of qtHookData
    QT_VERSION,

    // AddQObject, void(*)(QObject*), called for every constructed QObject
    // Note: this is called from the QObject constructor, ie. the sub-class
    // constructors haven't run yet.
    0,

    // RemoveQObject, void(*)(QObject*), called for every destructed QObject
    // Note: this is called from the QObject destructor, ie. the object
    // you get as an argument is already largely invalid.
    0,

    // Startup, void(*)(), called once QCoreApplication is operational
    0,

    // TypeInformationVersion, an integral value, bumped whenever private
    // object sizes or member offsets that are used in Qt Creator's
    // data structure "pretty printing" change.
    //
    // The required sizes and offsets are tested in tests/auto/other/toolsupport.
    // When this fails and the change was intentional, adjust the test and
    // adjust this value here.
    23
};

static_assert(QHooks::LastHookIndex == sizeof(qtHookData) / sizeof(qtHookData[0]));

QT_END_NAMESPACE

