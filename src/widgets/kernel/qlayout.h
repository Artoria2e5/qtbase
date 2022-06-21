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

#ifndef QLAYOUT_H
#define QLAYOUT_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qlayoutitem.h>
#include <QtWidgets/qsizepolicy.h>
#include <QtCore/qrect.h>
#include <QtCore/qmargins.h>

#include <limits.h>

QT_BEGIN_NAMESPACE


class QLayout;
class QSize;


class QLayoutPrivate;

class Q_WIDGETS_EXPORT QLayout : public QObject, public QLayoutItem
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QLayout)

    Q_PROPERTY(int spacing READ spacing WRITE setSpacing)
    Q_PROPERTY(QMargins contentsMargins READ contentsMargins WRITE setContentsMargins
               RESET unsetContentsMargins)
    Q_PROPERTY(SizeConstraint sizeConstraint READ sizeConstraint WRITE setSizeConstraint)
public:
    enum SizeConstraint {
        SetDefaultConstraint,
        SetNoConstraint,
        SetMinimumSize,
        SetFixedSize,
        SetMaximumSize,
        SetMinAndMaxSize
    };
    Q_ENUM(SizeConstraint)

    explicit QLayout(QWidget *parent = nullptr);
    ~QLayout();

    virtual int spacing() const;
    virtual void setSpacing(int);

    void setContentsMargins(int left, int top, int right, int bottom);
    void setContentsMargins(const QMargins &margins);
    void unsetContentsMargins();
    void getContentsMargins(int *left, int *top, int *right, int *bottom) const;
    QMargins contentsMargins() const;
    QRect contentsRect() const;

    bool setAlignment(QWidget *w, Qt::Alignment alignment);
    bool setAlignment(QLayout *l, Qt::Alignment alignment);
    using QLayoutItem::setAlignment;

    void setSizeConstraint(SizeConstraint);
    SizeConstraint sizeConstraint() const;
    void setMenuBar(QWidget *w);
    QWidget *menuBar() const;

    QWidget *parentWidget() const;

    void invalidate() override;
    QRect geometry() const override;
    bool activate();
    void update();

    void addWidget(QWidget *w);
    virtual void addItem(QLayoutItem *) = 0;

    void removeWidget(QWidget *w);
    void removeItem(QLayoutItem *);

    Qt::Orientations expandingDirections() const override;
    QSize minimumSize() const override;
    QSize maximumSize() const override;
    virtual void setGeometry(const QRect&) override;
    virtual QLayoutItem *itemAt(int index) const = 0;
    virtual QLayoutItem *takeAt(int index) = 0;
    virtual int indexOf(const QWidget *) const;
    virtual int indexOf(const QLayoutItem *) const;
    virtual int count() const = 0;
    bool isEmpty() const override;
    QSizePolicy::ControlTypes controlTypes() const override;

    virtual QLayoutItem *replaceWidget(QWidget *from, QWidget *to,
                                       Qt::FindChildOptions options = Qt::FindChildrenRecursively);

    int totalMinimumHeightForWidth(int w) const;
    int totalHeightForWidth(int w) const;
    QSize totalMinimumSize() const;
    QSize totalMaximumSize() const;
    QSize totalSizeHint() const;
    QLayout *layout() override;

    void setEnabled(bool);
    bool isEnabled() const;


    static QSize closestAcceptableSize(const QWidget *w, const QSize &s);

protected:
    void widgetEvent(QEvent *);
    void childEvent(QChildEvent *e) override;
    void addChildLayout(QLayout *l);
    void addChildWidget(QWidget *w);
    bool adoptLayout(QLayout *layout);

    QRect alignmentRect(const QRect&) const;
protected:
    QLayout(QLayoutPrivate &d, QLayout*, QWidget*);

private:
    Q_DISABLE_COPY(QLayout)

    static void activateRecursiveHelper(QLayoutItem *item);

    friend class QApplicationPrivate;
    friend class QWidget;

};

QT_END_NAMESPACE

//### support old includes
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qgridlayout.h>

#endif // QLAYOUT_H
