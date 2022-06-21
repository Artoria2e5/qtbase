/****************************************************************************
**
** Copyright (C) 2014 Robin Burchell <robin.burchell@viroteck.net>
** Copyright (C) 2022 The Qt Company Ltd.
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

#ifndef QOSCBUNDLE_P_H
#define QOSCBUNDLE_P_H

#include "qoscmessage_p.h"

#include <QtCore/QList>

QT_BEGIN_NAMESPACE

class QByteArray;

class QOscBundle
{
    QOscBundle(); // for QList, don't use
    friend class QList<QOscBundle>;
public:
    explicit QOscBundle(const QByteArray &data);

    bool isValid() const { return m_isValid; }
    QList<QOscBundle> bundles() const { return m_bundles; }
    QList<QOscMessage> messages() const { return m_messages; }

private:
    bool m_isValid;
    bool m_immediate;
    quint32 m_timeEpoch;
    quint32 m_timePico;
    QList<QOscBundle> m_bundles;
    QList<QOscMessage> m_messages;
};
Q_DECLARE_TYPEINFO(QOscBundle, Q_RELOCATABLE_TYPE);

QT_END_NAMESPACE

#endif // QOSCBUNDLE_P_H
