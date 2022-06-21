/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Copyright (C) 2016 Intel Corporation.
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

#ifndef QURL_P_H
#define QURL_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API. It exists for the convenience of
// qurl*.cpp This header file may change from version to version without
// notice, or even be removed.
//
// We mean it.
//

#include <QtCore/private/qglobal_p.h>
#include "qurl.h"

QT_BEGIN_NAMESPACE

// in qurlrecode.cpp
extern Q_AUTOTEST_EXPORT qsizetype qt_urlRecode(QString &appendTo, QStringView url,
                                                QUrl::ComponentFormattingOptions encoding,
                                                const ushort *tableModifications = nullptr);

// in qurlidna.cpp
enum AceLeadingDot { AllowLeadingDot, ForbidLeadingDot };
enum AceOperation { ToAceOnly, NormalizeAce };
extern QString qt_ACE_do(QStringView domain, AceOperation op, AceLeadingDot dot);
extern Q_AUTOTEST_EXPORT bool qt_nameprep(QString *source, int from);
extern Q_AUTOTEST_EXPORT bool qt_check_std3rules(QStringView in);
extern Q_AUTOTEST_EXPORT void qt_punycodeEncoder(QStringView in, QString *output);
extern Q_AUTOTEST_EXPORT QString qt_punycodeDecoder(const QString &pc);

QT_END_NAMESPACE

#endif // QURL_P_H
