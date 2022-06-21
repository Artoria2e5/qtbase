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

#ifndef QTEXTBROWSER_H
#define QTEXTBROWSER_H

#include <QtWidgets/qtwidgetsglobal.h>
#include <QtWidgets/qtextedit.h>
#include <QtCore/qurl.h>

QT_REQUIRE_CONFIG(textbrowser);

QT_BEGIN_NAMESPACE

class QTextBrowserPrivate;

class Q_WIDGETS_EXPORT QTextBrowser : public QTextEdit
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource)
    Q_PROPERTY(QTextDocument::ResourceType sourceType READ sourceType)
    Q_OVERRIDE(bool modified SCRIPTABLE false)
    Q_OVERRIDE(bool readOnly DESIGNABLE false SCRIPTABLE false)
    Q_OVERRIDE(bool undoRedoEnabled DESIGNABLE false SCRIPTABLE false)
    Q_PROPERTY(QStringList searchPaths READ searchPaths WRITE setSearchPaths)
    Q_PROPERTY(bool openExternalLinks READ openExternalLinks WRITE setOpenExternalLinks)
    Q_PROPERTY(bool openLinks READ openLinks WRITE setOpenLinks)

public:
    explicit QTextBrowser(QWidget* parent = nullptr);
    virtual ~QTextBrowser();

    QUrl source() const;
    QTextDocument::ResourceType sourceType() const;

    QStringList searchPaths() const;
    void setSearchPaths(const QStringList &paths);

    virtual QVariant loadResource(int type, const QUrl &name) override;

    bool isBackwardAvailable() const;
    bool isForwardAvailable() const;
    void clearHistory();
    QString historyTitle(int) const;
    QUrl historyUrl(int) const;
    int backwardHistoryCount() const;
    int forwardHistoryCount() const;

    bool openExternalLinks() const;
    void setOpenExternalLinks(bool open);

    bool openLinks() const;
    void setOpenLinks(bool open);

public Q_SLOTS:
    void setSource(const QUrl &name, QTextDocument::ResourceType type = QTextDocument::UnknownResource);
    virtual void backward();
    virtual void forward();
    virtual void home();
    virtual void reload();

Q_SIGNALS:
    void backwardAvailable(bool);
    void forwardAvailable(bool);
    void historyChanged();
    void sourceChanged(const QUrl &);
    void highlighted(const QUrl &);
    void anchorClicked(const QUrl &);

protected:
    bool event(QEvent *e) override;
    virtual void keyPressEvent(QKeyEvent *ev) override;
    virtual void mouseMoveEvent(QMouseEvent *ev) override;
    virtual void mousePressEvent(QMouseEvent *ev) override;
    virtual void mouseReleaseEvent(QMouseEvent *ev) override;
    virtual void focusOutEvent(QFocusEvent *ev) override;
    virtual bool focusNextPrevChild(bool next) override;
    virtual void paintEvent(QPaintEvent *e) override;
    virtual void doSetSource(const QUrl &name, QTextDocument::ResourceType type = QTextDocument::UnknownResource);

private:
    Q_DISABLE_COPY(QTextBrowser)
    Q_DECLARE_PRIVATE(QTextBrowser)
    Q_PRIVATE_SLOT(d_func(), void _q_documentModified())
    Q_PRIVATE_SLOT(d_func(), void _q_activateAnchor(const QString &))
    Q_PRIVATE_SLOT(d_func(), void _q_highlightLink(const QString &))
};

QT_END_NAMESPACE

#endif // QTEXTBROWSER_H
