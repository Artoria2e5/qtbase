/***************************************************************************
**
** Copyright (C) 2018 QNX Software Systems. All rights reserved.
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

#include "qqnxforeignwindow.h"
#include "qqnxintegration.h"

QT_BEGIN_NAMESPACE

QQnxForeignWindow::QQnxForeignWindow(QWindow *window,
                                     screen_context_t context,
                                     screen_window_t screenWindow)
    : QQnxWindow(window, context, screenWindow)
{
    initWindow();
}

bool QQnxForeignWindow::isForeignWindow() const
{
    return true;
}

int QQnxForeignWindow::pixelFormat() const
{
    int result = SCREEN_FORMAT_RGBA8888;
    screen_get_window_property_iv(nativeHandle(), SCREEN_PROPERTY_FORMAT, &result);
    return result;
}

QT_END_NAMESPACE
