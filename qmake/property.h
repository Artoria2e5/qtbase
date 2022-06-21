/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the qmake application of the Qt Toolkit.
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
******************************************************************************/

#ifndef PROPERTY_H
#define PROPERTY_H

#include "library/proitems.h"
#include "propertyprinter.h"

#include <qglobal.h>
#include <qstring.h>
#include <qhash.h>

QT_BEGIN_NAMESPACE

class QSettings;

class QMakeProperty final
{
    QSettings *settings;
    void initSettings();

    QHash<ProKey, ProString> m_values;

public:
    QMakeProperty();
    ~QMakeProperty();

    void reload();

    bool hasValue(const ProKey &);
    ProString value(const ProKey &);

    void setValue(QString, const QString &);
    void remove(const QString &);

    int queryProperty(const QStringList &optionProperties = QStringList(),
                      const PropertyPrinter &printer = qmakePropertyPrinter);
    int setProperty(const QStringList &optionProperties);
    void unsetProperty(const QStringList &optionProperties);
};

QT_END_NAMESPACE

#endif // PROPERTY_H
