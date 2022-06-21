/***************************************************************************
**
** Copyright (C) 2013 BlackBerry Limited. All rights reserved.
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

#ifndef QQNXSCREENEVENTFILTER_H
#define QQNXSCREENEVENTFILTER_H

QT_BEGIN_NAMESPACE

class QQnxScreenEventFilter
{
protected:
    ~QQnxScreenEventFilter() {}

public:
    virtual bool handleKeyboardEvent(int flags, int sym, int mod, int scan, int cap, int sequenceId) = 0;
};

QT_END_NAMESPACE

#endif
