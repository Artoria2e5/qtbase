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

#ifndef QEASINGCURVE_H
#define QEASINGCURVE_H

#include <QtCore/qglobal.h>

QT_REQUIRE_CONFIG(easingcurve);

#include <QtCore/qlist.h>
#include <QtCore/qobjectdefs.h>

QT_BEGIN_NAMESPACE

class QEasingCurvePrivate;
class QPointF;
class Q_CORE_EXPORT QEasingCurve
{
    Q_GADGET
public:
    enum Type {
        Linear,
        InQuad, OutQuad, InOutQuad, OutInQuad,
        InCubic, OutCubic, InOutCubic, OutInCubic,
        InQuart, OutQuart, InOutQuart, OutInQuart,
        InQuint, OutQuint, InOutQuint, OutInQuint,
        InSine, OutSine, InOutSine, OutInSine,
        InExpo, OutExpo, InOutExpo, OutInExpo,
        InCirc, OutCirc, InOutCirc, OutInCirc,
        InElastic, OutElastic, InOutElastic, OutInElastic,
        InBack, OutBack, InOutBack, OutInBack,
        InBounce, OutBounce, InOutBounce, OutInBounce,
        InCurve, OutCurve, SineCurve, CosineCurve,
        BezierSpline, TCBSpline, Custom, NCurveTypes
    };
    Q_ENUM(Type)

    QEasingCurve(Type type = Linear);
    QEasingCurve(const QEasingCurve &other);
    ~QEasingCurve();

    QEasingCurve &operator=(const QEasingCurve &other)
    { if ( this != &other ) { QEasingCurve copy(other); swap(copy); } return *this; }
    QEasingCurve(QEasingCurve &&other) noexcept : d_ptr(other.d_ptr) { other.d_ptr = nullptr; }
    QT_MOVE_ASSIGNMENT_OPERATOR_IMPL_VIA_PURE_SWAP(QEasingCurve)

    void swap(QEasingCurve &other) noexcept { qt_ptr_swap(d_ptr, other.d_ptr); }

    bool operator==(const QEasingCurve &other) const;
    inline bool operator!=(const QEasingCurve &other) const
    { return !(this->operator==(other)); }

    qreal amplitude() const;
    void setAmplitude(qreal amplitude);

    qreal period() const;
    void setPeriod(qreal period);

    qreal overshoot() const;
    void setOvershoot(qreal overshoot);

    void addCubicBezierSegment(const QPointF &c1, const QPointF &c2, const QPointF &endPoint);
    void addTCBSegment(const QPointF &nextPoint, qreal t, qreal c, qreal b);
    QList<QPointF> toCubicSpline() const;

    Type type() const;
    void setType(Type type);
    typedef qreal (*EasingFunction)(qreal progress);
    void setCustomType(EasingFunction func);
    EasingFunction customType() const;

    qreal valueForProgress(qreal progress) const;

private:
    QEasingCurvePrivate *d_ptr;
#ifndef QT_NO_DEBUG_STREAM
    friend Q_CORE_EXPORT QDebug operator<<(QDebug debug, const QEasingCurve &item);
#endif
#ifndef QT_NO_DATASTREAM
    friend Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const QEasingCurve &);
    friend Q_CORE_EXPORT QDataStream &operator>>(QDataStream &, QEasingCurve &);
#endif
};
Q_DECLARE_SHARED(QEasingCurve)

#ifndef QT_NO_DEBUG_STREAM
Q_CORE_EXPORT QDebug operator<<(QDebug debug, const QEasingCurve &item);
#endif

#ifndef QT_NO_DATASTREAM
Q_CORE_EXPORT QDataStream &operator<<(QDataStream &, const QEasingCurve &);
Q_CORE_EXPORT QDataStream &operator>>(QDataStream &, QEasingCurve &);
#endif

QT_END_NAMESPACE

#endif
