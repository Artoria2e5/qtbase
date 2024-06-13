// Copyright (C) 2024 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QtNetwork/qformdatabuilder.h>

#include <QtCore/qbuffer.h>
#include <QtCore/qfile.h>

#include <QtTest/qtest.h>

using namespace Qt::StringLiterals;

class tst_QFormDataBuilder : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void generateQHttpPartWithDevice_data();
    void generateQHttpPartWithDevice();

    void escapesBackslashAndQuotesInFilenameAndName_data();
    void escapesBackslashAndQuotesInFilenameAndName();

    void picksUtf8EncodingOnlyIfL1OrAsciiDontSuffice_data();
    void picksUtf8EncodingOnlyIfL1OrAsciiDontSuffice();

    void setHeadersDoesNotAffectHeaderFieldsManagedByBuilder_data();
    void setHeadersDoesNotAffectHeaderFieldsManagedByBuilder();

    void specifyMimeType_data();
    void specifyMimeType();
};

void tst_QFormDataBuilder::generateQHttpPartWithDevice_data()
{
    QTest::addColumn<QLatin1StringView>("name_data");
    QTest::addColumn<QString>("real_file_name");
    QTest::addColumn<QString>("body_name_data");
    QTest::addColumn<QByteArray>("expected_content_type_data");
    QTest::addColumn<QByteArray>("expected_content_disposition_data");

    QTest::newRow("txt-ascii") << "text"_L1 << "rfc3252.txt" << "rfc3252.txt" << "text/plain"_ba
                               << "form-data; name=\"text\"; filename=rfc3252.txt"_ba;
    QTest::newRow("txt-latin") << "text"_L1 << "rfc3252.txt" << "szöveg.txt" << "text/plain"_ba
                               << "form-data; name=\"text\"; filename*=ISO-8859-1''sz%F6veg.txt"_ba;
    QTest::newRow("txt-unicode") << "text"_L1 << "rfc3252.txt" << "テキスト.txt" << "text/plain"_ba
                                 << "form-data; name=\"text\"; filename*=UTF-8''%E3%83%86%E3%82%AD%E3%82%B9%E3%83%88.txt"_ba;

    QTest::newRow("jpg-ascii") << "image"_L1 << "image1.jpg" << "image1.jpg" << "image/jpeg"_ba
                               << "form-data; name=\"image\"; filename=image1.jpg"_ba;
    QTest::newRow("jpg-latin") << "image"_L1 << "image1.jpg" << "kép.jpg" << "image/jpeg"_ba
                               << "form-data; name=\"image\"; filename*=ISO-8859-1''k%E9p.jpg"_ba;
    QTest::newRow("jpg-unicode") << "image"_L1 << "image1.jpg" << "絵.jpg" << "image/jpeg"_ba
                                 << "form-data; name=\"image\"; filename*=UTF-8''%E7%B5%B5"_ba;

    QTest::newRow("doc-ascii") << "text"_L1 << "document.docx" << "word.docx"
                               << "application/vnd.openxmlformats-officedocument.wordprocessingml.document"_ba
                               << "form-data; name=\"text\"; filename=word.docx"_ba;
    QTest::newRow("doc-latin") << "text"_L1 << "document.docx" << "szöveg.docx"
                               << "application/vnd.openxmlformats-officedocument.wordprocessingml.document"_ba
                               << "form-data; name=\"text\"; filename*=ISO-8859-1''sz%F6veg.docx"_ba;
    QTest::newRow("doc-unicode") << "text"_L1 << "document.docx" << "テキスト.docx"
                                 << "application/vnd.openxmlformats-officedocument.wordprocessingml.document"_ba
                                 << "form-data; name=\"text\"; filename*=UTF-8''%E3%83%86%E3%82%AD%E3%82%B9%E3%83%88.docx"_ba;

    QTest::newRow("xls-ascii") << "spreadsheet"_L1 << "sheet.xlsx" << "sheet.xlsx"
                               << "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"_ba
                               << "form-data; name=\"spreadsheet\"; filename=sheet.xlsx"_ba;
    QTest::newRow("xls-latin") << "spreadsheet"_L1 << "sheet.xlsx" << "szöveg.xlsx"
                               << "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"_ba
                               << "form-data; name=\"spreadsheet\"; filename*=ISO-8859-1''sz%F6veg.xlsx"_ba;
    QTest::newRow("xls-unicode") << "spreadsheet"_L1 << "sheet.xlsx" << "テキスト.xlsx"
                                 << "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"_ba
                                 << "form-data; name=\"spreadsheet\"; filename*=UTF-8''%E3%83%86%E3%82%AD%E3%82%B9%E3%83%88.xlsx"_ba;

}

void tst_QFormDataBuilder::generateQHttpPartWithDevice()
{
    QFETCH(const QLatin1StringView, name_data);
    QFETCH(const QString, real_file_name);
    QFETCH(const QString, body_name_data);
    QFETCH(const QByteArray, expected_content_type_data);
    QFETCH(const QByteArray, expected_content_disposition_data);

    QString testData = QFileInfo(QFINDTESTDATA(real_file_name)).absoluteFilePath();
    QFile data_file(testData);

    QHttpPart httpPart = QFormDataPartBuilder(name_data, QFormDataPartBuilder::PrivateConstructor())
                        .setBodyDevice(&data_file, body_name_data)
                        .build();

    QByteArray msg;
    {
        QBuffer buf(&msg);
        QVERIFY(buf.open(QIODevice::WriteOnly));
        QDebug debug(&buf);
        debug << httpPart;
    }

    QVERIFY(msg.contains(expected_content_type_data));
    QVERIFY(msg.contains(expected_content_disposition_data));
}

void tst_QFormDataBuilder::escapesBackslashAndQuotesInFilenameAndName_data()
{
    QTest::addColumn<QLatin1StringView>("name_data");
    QTest::addColumn<QString>("body_name_data");
    QTest::addColumn<QByteArray>("expected_content_type_data");
    QTest::addColumn<QByteArray>("expected_content_disposition_data");

    QTest::newRow("quote") << "t\"ext"_L1 << "rfc3252.txt" << "text/plain"_ba
                           << R"(form-data; name="t\"ext"; filename=rfc3252.txt)"_ba;

    QTest::newRow("slash") << "t\\ext"_L1 << "rfc3252.txt" << "text/plain"_ba
                           << R"(form-data; name="t\\ext"; filename=rfc3252.txt)"_ba;

    QTest::newRow("quotes") << "t\"e\"xt"_L1 << "rfc3252.txt" << "text/plain"_ba
                            << R"(form-data; name="t\"e\"xt"; filename=rfc3252.txt)"_ba;

    QTest::newRow("slashes") << "t\\\\ext"_L1 << "rfc3252.txt" << "text/plain"_ba
                             << R"(form-data; name="t\\\\ext"; filename=rfc3252.txt)"_ba;

    QTest::newRow("quote-slash") << "t\"ex\\t"_L1 << "rfc3252.txt" << "text/plain"_ba
                                 << R"(form-data; name="t\"ex\\t"; filename=rfc3252.txt)"_ba;

    QTest::newRow("quotes-slashes") << "t\"e\"x\\t\\"_L1 << "rfc3252.txt" << "text/plain"_ba
                                    << R"(form-data; name="t\"e\"x\\t\\"; filename=rfc3252.txt)"_ba;
}

void tst_QFormDataBuilder::escapesBackslashAndQuotesInFilenameAndName()
{
    QFETCH(const QLatin1StringView, name_data);
    QFETCH(const QString, body_name_data);
    QFETCH(const QByteArray, expected_content_type_data);
    QFETCH(const QByteArray, expected_content_disposition_data);

    QFile dummy_file(body_name_data);

    QHttpPart httpPart = QFormDataPartBuilder(name_data, QFormDataPartBuilder::PrivateConstructor())
                        .setBodyDevice(&dummy_file, body_name_data)
                        .build();

    QByteArray msg;
    {
        QBuffer buf(&msg);
        QVERIFY(buf.open(QIODevice::WriteOnly));
        QDebug debug(&buf);
        debug << httpPart;
    }

    QVERIFY(msg.contains(expected_content_type_data));
    QVERIFY(msg.contains(expected_content_disposition_data));
}

void tst_QFormDataBuilder::picksUtf8EncodingOnlyIfL1OrAsciiDontSuffice_data()
{
    QTest::addColumn<QLatin1StringView>("name_data");
    QTest::addColumn<QAnyStringView>("body_name_data");
    QTest::addColumn<QByteArray>("expected_content_type_data");
    QTest::addColumn<QByteArray>("expected_content_disposition_data");

    QTest::newRow("latin1-ascii") << "text"_L1 << QAnyStringView("rfc3252.txt"_L1) << "text/plain"_ba
                                  << "form-data; name=\"text\"; filename=rfc3252.txt"_ba;
    QTest::newRow("u8-ascii") << "text"_L1 << QAnyStringView(u8"rfc3252.txt") << "text/plain"_ba
                              << "form-data; name=\"text\"; filename=rfc3252.txt"_ba;
    QTest::newRow("u-ascii") << "text"_L1 << QAnyStringView(u"rfc3252.txt") << "text/plain"_ba
                             << "form-data; name=\"text\"; filename=rfc3252.txt"_ba;


    QTest::newRow("latin1-latin") << "text"_L1 << QAnyStringView("sz\366veg.txt"_L1) << "text/plain"_ba
                                  << "form-data; name=\"text\"; filename*=ISO-8859-1''sz%F6veg.txt"_ba;
    QTest::newRow("u8-latin") << "text"_L1 << QAnyStringView(u8"szöveg.txt") << "text/plain"_ba
                              << "form-data; name=\"text\"; filename*=ISO-8859-1''sz%F6veg.txt"_ba;
    QTest::newRow("u-latin") << "text"_L1 << QAnyStringView(u"szöveg.txt") << "text/plain"_ba
                             << "form-data; name=\"text\"; filename*=ISO-8859-1''sz%F6veg.txt"_ba;

    QTest::newRow("u8-u8") << "text"_L1 << QAnyStringView(u8"テキスト.txt") << "text/plain"_ba
                           << "form-data; name=\"text\"; filename*=UTF-8''%E3%83%86%E3%82%AD%E3%82%B9%E3%83%88.txt"_ba;
}

void tst_QFormDataBuilder::picksUtf8EncodingOnlyIfL1OrAsciiDontSuffice()
{
    QFETCH(const QLatin1StringView, name_data);
    QFETCH(const QAnyStringView, body_name_data);
    QFETCH(const QByteArray, expected_content_type_data);
    QFETCH(const QByteArray, expected_content_disposition_data);

    QBuffer buff;

    QHttpPart httpPart = QFormDataPartBuilder(name_data, QFormDataPartBuilder::PrivateConstructor())
                        .setBodyDevice(&buff, body_name_data)
                        .build();

    QByteArray msg;
    {
        QBuffer buf(&msg);
        QVERIFY(buf.open(QIODevice::WriteOnly));
        QDebug debug(&buf);
        debug << httpPart;
    }

    QVERIFY(msg.contains(expected_content_type_data));
    QVERIFY(msg.contains(expected_content_disposition_data));
}

void tst_QFormDataBuilder::setHeadersDoesNotAffectHeaderFieldsManagedByBuilder_data()
{
    QTest::addColumn<QLatin1StringView>("name_data");
    QTest::addColumn<QAnyStringView>("body_name_data");
    QTest::addColumn<bool>("overwrite");
    QTest::addColumn<bool>("extra_headers");
    QTest::addColumn<QStringList>("expected_headers");

    QTest::newRow("content-disposition-is-set-by-default")
            << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
            << false << false
            << QStringList{
                uR"("content-disposition":"form-data; name=\"text\"; filename=rfc3252.txt")"_s,
                uR"("content-type":"text/plain")"_s};

    QTest::newRow("default-overwrites-preset-content-disposition")
            << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
            << true << false
            << QStringList{
                uR"("content-disposition":"form-data; name=\"text\"; filename=rfc3252.txt")"_s,
                uR"("content-type":"text/plain")"_s};

    QTest::newRow("added-extra-header")
            << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
            << false << true
            << QStringList{
                uR"("content-disposition":"form-data; name=\"text\"; filename=rfc3252.txt")"_s,
                uR"("content-type":"text/plain")"_s,
                uR"("content-length":"70")"_s};

    QTest::newRow("extra-header-and-overwrite")
            << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
            << true << true
            << QStringList{
                uR"("content-disposition":"form-data; name=\"text\"; filename=rfc3252.txt")"_s,
                uR"("content-type":"text/plain")"_s,
                uR"("content-length":"70")"_s};
}

void tst_QFormDataBuilder::setHeadersDoesNotAffectHeaderFieldsManagedByBuilder()
{
    QFETCH(const QLatin1StringView, name_data);
    QFETCH(const QAnyStringView, body_name_data);
    QFETCH(const bool, overwrite);
    QFETCH(const bool, extra_headers);
    QFETCH(const QStringList, expected_headers);

    QBuffer buff;

    QFormDataBuilder qfdb;
    QFormDataPartBuilder &qfdpb = qfdb.part(name_data).setBodyDevice(&buff, body_name_data);

    if (overwrite || extra_headers) {
        QHttpHeaders headers;

        if (overwrite) {
            headers.append(QHttpHeaders::WellKnownHeader::ContentType, "attachment");
            qfdpb.setHeaders(headers);
        }

        if (extra_headers) {
            headers.append(QHttpHeaders::WellKnownHeader::ContentLength, "70");
            qfdpb.setHeaders(std::move(headers));
        }
    }

    const QHttpPart httpPart = qfdpb.build();

    const auto msg = QDebug::toString(httpPart);
    for (const auto &header : expected_headers)
        QVERIFY2(msg.contains(header), qPrintable(header));
}

void tst_QFormDataBuilder::specifyMimeType_data()
{
    QTest::addColumn<QLatin1StringView>("name_data");
    QTest::addColumn<QAnyStringView>("body_name_data");
    QTest::addColumn<QAnyStringView>("mime_type");
    QTest::addColumn<QString>("expected_content_type_data");

    QTest::newRow("not-specified") << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
        << QAnyStringView("text/plain"_L1) << uR"("content-type":"text/plain")"_s;
    QTest::newRow("mime-specified") << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
        << QAnyStringView("text/plain"_L1) << uR"("content-type":"text/plain")"_s;
    // wrong mime type specified but it is not overridden by the deduction
    QTest::newRow("wrong-mime-specified") << "text"_L1 << QAnyStringView("rfc3252.txt"_L1)
        << QAnyStringView("image/jpeg"_L1) << uR"("content-type":"image/jpeg)"_s;
}

void tst_QFormDataBuilder::specifyMimeType()
{
    QFETCH(const QLatin1StringView, name_data);
    QFETCH(const QAnyStringView, body_name_data);
    QFETCH(const QAnyStringView, mime_type);
    QFETCH(const QString, expected_content_type_data);

    QBuffer buff;

    QFormDataBuilder qfdb;
    QFormDataPartBuilder &qfdpb = qfdb.part(name_data).setBodyDevice(&buff, body_name_data);

    if (!mime_type.empty())
        qfdpb.setBodyDevice(&buff, body_name_data, mime_type);
    else
        qfdpb.setBodyDevice(&buff, body_name_data);

    const QHttpPart httpPart = qfdpb.build();

    const auto msg = QDebug::toString(httpPart);
    QVERIFY(msg.contains(expected_content_type_data));
}


QTEST_MAIN(tst_QFormDataBuilder)
#include "tst_qformdatabuilder.moc"
