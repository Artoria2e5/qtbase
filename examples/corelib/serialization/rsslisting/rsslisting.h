// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef RSSLISTING_H
#define RSSLISTING_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QWidget>
#include <QXmlStreamReader>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QTreeWidget;
class QTreeWidgetItem;
class QUrl;
QT_END_NAMESPACE

class RSSListing : public QWidget
{
    Q_OBJECT
public:
    explicit RSSListing(const QString &url = QString(), QWidget *widget = nullptr);

public slots:
    void fetch();
    void finished(QNetworkReply *reply);
    void readyRead();
    void error(QNetworkReply::NetworkError);

private:
    void parseXml();
    void get(const QUrl &url);

    QXmlStreamReader xml;
    QString currentTag;
    QString linkString;
    QString titleString;

    QNetworkAccessManager manager;
    QNetworkReply *currentReply;

    QLineEdit *lineEdit;
    QTreeWidget *treeWidget;
    QPushButton *fetchButton;
};

#endif
