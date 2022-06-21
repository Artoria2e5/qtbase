/****************************************************************************
**
** Copyright (C) 2022 The Qt Company Ltd.
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

#import <UIKit/UIKit.h>

#include "qiosimagepickercontroller.h"

@implementation QIOSImagePickerController {
    QIOSFileDialog *m_fileDialog;
}

- (instancetype)initWithQIOSFileDialog:(QIOSFileDialog *)fileDialog
{
    self = [super init];
    if (self) {
        m_fileDialog = fileDialog;
        self.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
        self.delegate = self;
    }
    return self;
}

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    Q_UNUSED(picker);
    NSURL *url = info[UIImagePickerControllerReferenceURL];
    QUrl fileUrl = QUrl::fromLocalFile(QString::fromNSString(url.description));
    m_fileDialog->selectedFilesChanged(QList<QUrl>() << fileUrl);
    emit m_fileDialog->accept();
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker
{
    Q_UNUSED(picker);
    emit m_fileDialog->reject();
}

@end
