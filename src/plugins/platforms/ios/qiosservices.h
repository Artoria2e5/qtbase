/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef QIOSSERVICES_H
#define QIOSSERVICES_H

#include <qurl.h>
#include <qpa/qplatformservices.h>

QT_BEGIN_NAMESPACE

class QIOSServices : public QPlatformServices
{
public:
    bool openUrl(const QUrl &url);
    bool openDocument(const QUrl &url);

    bool handleUrl(const QUrl &url);

private:
    QUrl m_handlingUrl;
};

QT_END_NAMESPACE

#endif // QIOSSERVICES_H
