/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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
****************************************************************************/

#ifndef QWINDOWSUIAACCESSIBILITY_H
#define QWINDOWSUIAACCESSIBILITY_H

#include <QtGui/qtguiglobal.h>
#if QT_CONFIG(accessibility)

#include "qwindowscontext.h"
#include <qpa/qplatformaccessibility.h>

QT_BEGIN_NAMESPACE

// Windows platform accessibility implemented over UI Automation.
class QWindowsUiaAccessibility : public QPlatformAccessibility
{
public:
    explicit QWindowsUiaAccessibility();
    virtual ~QWindowsUiaAccessibility();
    static bool handleWmGetObject(HWND hwnd, WPARAM wParam, LPARAM lParam, LRESULT *lResult);
    void notifyAccessibilityUpdate(QAccessibleEvent *event) override;
private:
    static bool m_accessibleActive;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(accessibility)

#endif // QWINDOWSUIAACCESSIBILITY_H
