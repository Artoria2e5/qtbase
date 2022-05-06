/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
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
****************************************************************************/

#include "qplatformintegrationplugin.h"

QT_BEGIN_NAMESPACE

QPlatformIntegrationPlugin::QPlatformIntegrationPlugin(QObject *parent)
    : QObject(parent)
{
}

QPlatformIntegrationPlugin::~QPlatformIntegrationPlugin()
{
}

QPlatformIntegration *QPlatformIntegrationPlugin::create(const QString &key, const QStringList &paramList)
{
    Q_UNUSED(key)
    Q_UNUSED(paramList);
    return nullptr;
}

QPlatformIntegration *QPlatformIntegrationPlugin::create(const QString &key, const QStringList &paramList, int &argc, char **argv)
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    return create(key, paramList); // Fallback for platform plugins that do not implement the argc/argv version.
}

QT_END_NAMESPACE

#include "moc_qplatformintegrationplugin.cpp"
