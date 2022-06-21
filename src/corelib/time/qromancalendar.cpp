/****************************************************************************
**
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

#include "qglobal.h"
#include "qromancalendar_p.h"
#include "qromancalendar_data_p.h"

QT_BEGIN_NAMESPACE

/*!
    \since 5.14

    \class QRomanCalendar
    \inmodule QtCore
    \brief The QRomanCalendar class is a shared base for calendars based on the
    ancient Roman calendar.

    \section1

    Calendars based on the ancient Roman calendar share the names of months,
    whose lengths depend in a common way on whether the year is a leap
    year. They differ in how they determine which years are leap years.

    \sa QGregorianCalendar, QJulianCalendar, QMilankovicCalendar
*/

int QRomanCalendar::daysInMonth(int month, int year) const
{
    if (!year || month < 1 || month > 12)
        return 0;

    if (month == 2)
        return isLeapYear(year) ? 29 : 28;

    // Long if odd up to July = 7, or if even from 8 = August onwards:
    return 30 | ((month & 1) ^ (month >> 3));
}

int QRomanCalendar::minimumDaysInMonth() const
{
    return 28;
}

bool QRomanCalendar::isLunar() const
{
    return false;
}

bool QRomanCalendar::isLuniSolar() const
{
    return false;
}

bool QRomanCalendar::isSolar() const
{
    return true;
}

const QCalendarLocale *QRomanCalendar::localeMonthIndexData() const
{
    return locale_data;
}

const char16_t *QRomanCalendar::localeMonthData() const
{
    return months_data;
}

QT_END_NAMESPACE
