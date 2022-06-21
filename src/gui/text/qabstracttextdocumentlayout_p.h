/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtGui module of the Qt Toolkit.
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

#ifndef QABSTRACTTEXTDOCUMENTLAYOUT_P_H
#define QABSTRACTTEXTDOCUMENTLAYOUT_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <QtGui/private/qtguiglobal_p.h>
#include "private/qobject_p.h"
#include "qtextdocument_p.h"
#include "QtCore/qhash.h"

QT_BEGIN_NAMESPACE

struct QTextObjectHandler
{
    QTextObjectHandler() : iface(nullptr) {}
    QTextObjectInterface *iface;
    QPointer<QObject> component;
};
typedef QHash<int, QTextObjectHandler> HandlerHash;

class Q_GUI_EXPORT QAbstractTextDocumentLayoutPrivate : public QObjectPrivate
{
public:
    Q_DECLARE_PUBLIC(QAbstractTextDocumentLayout)

    inline QAbstractTextDocumentLayoutPrivate()
        : paintDevice(nullptr) {}
    ~QAbstractTextDocumentLayoutPrivate();

    inline void setDocument(QTextDocument *doc) {
        document = doc;
        docPrivate = nullptr;
        if (doc)
            docPrivate = QTextDocumentPrivate::get(doc);
    }

    inline int _q_dynamicPageCountSlot() const
    { return q_func()->pageCount(); }
    inline QSizeF _q_dynamicDocumentSizeSlot() const
    { return q_func()->documentSize(); }

    HandlerHash handlers;

    void _q_handlerDestroyed(QObject *obj);
    QPaintDevice *paintDevice;

    QTextDocument *document;
    QTextDocumentPrivate *docPrivate;
};

QT_END_NAMESPACE

#endif // QABSTRACTTEXTDOCUMENTLAYOUT_P_H
