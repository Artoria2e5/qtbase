/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWidgets module of the Qt Toolkit.
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

#ifndef QCOLORMAP_H
#define QCOLORMAP_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtGui/qrgb.h>
#include <QtGui/qwindowdefs.h>
#include <QtCore/qatomic.h>
#include <QtCore/qlist.h>

QT_BEGIN_NAMESPACE


class QColor;
class QColormapPrivate;

class Q_WIDGETS_EXPORT QColormap
{
public:
    enum Mode { Direct, Indexed, Gray };

    static void initialize();
    static void cleanup();

    static QColormap instance(int screen = -1);

    QColormap(const QColormap &colormap);
    ~QColormap();

    QColormap &operator=(const QColormap &colormap);

    Mode mode() const;

    int depth() const;
    int size() const;

    uint pixel(const QColor &color) const;
    const QColor colorAt(uint pixel) const;

    const QList<QColor> colormap() const;

private:
    QColormap();
    QColormapPrivate *d;
};

QT_END_NAMESPACE

#endif // QCOLORMAP_H
