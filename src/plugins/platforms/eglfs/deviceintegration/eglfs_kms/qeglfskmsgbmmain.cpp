/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Copyright (C) 2016 Pelagicore AG
** Contact: https://www.qt.io/licensing/
**
** This file is part of the qmake spec of the Qt Toolkit.
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

#include "private/qeglfsdeviceintegration_p.h"
#include "qeglfskmsgbmintegration_p.h"

QT_BEGIN_NAMESPACE

class QEglFSKmsGbmIntegrationPlugin : public QEglFSDeviceIntegrationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QEglFSDeviceIntegrationFactoryInterface_iid FILE "eglfs_kms.json")

public:
    QEglFSDeviceIntegration *create() override { return new QEglFSKmsGbmIntegration; }
};

QT_END_NAMESPACE

#include "qeglfskmsgbmmain.moc"
