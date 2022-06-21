/****************************************************************************
**
** Copyright (C) 2019 BogDan Vatra <bogdan@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
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


#include <qpa/qplatformintegrationplugin.h>
#include "qandroidplatformintegration.h"

QT_BEGIN_NAMESPACE

class QAndroidIntegrationPlugin : public QPlatformIntegrationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformIntegrationFactoryInterface_iid FILE "android.json")

public:
    QPlatformIntegration *create(const QString& system, const QStringList& paramList) override;
};

QPlatformIntegration *QAndroidIntegrationPlugin::create(const QString& system, const QStringList& paramList)
{
    if (!system.compare(QLatin1String("android"), Qt::CaseInsensitive))
        return new QAndroidPlatformIntegration(paramList);

    return nullptr;
}

QT_END_NAMESPACE
#include "main.moc"
