/****************************************************************************
 **
 ** Copyright (C) 2006-2008 Trolltech ASA. All rights reserved.
 **
 ** This file is part of the example classes of the Qt Toolkit.
 **
 ** Licensees holding a valid Qt License Agreement may use this file in
 ** accordance with the rights, responsibilities and obligations
 ** contained therein.  Please consult your licensing agreement or
 ** contact sales@trolltech.com if any conditions of this licensing
 ** agreement are not clear to you.
 **
 ** Further information about Qt licensing is available at:
 ** http://www.trolltech.com/products/qt/licensing.html or by
 ** contacting info@trolltech.com.
 **
 ** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 ** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 **
 ****************************************************************************/

 #include <QtGui>

 #include "window.h"

 void addMail(QAbstractItemModel *model, const QString &subject,
              const QString &sender, const QDateTime &date)
 {
     model->insertRow(0);
     model->setData(model->index(0, 0), subject);
     model->setData(model->index(0, 1), sender);
     model->setData(model->index(0, 2), date);
 }

 QAbstractItemModel *createMailModel(QObject *parent)
 {
     QStandardItemModel *model = new QStandardItemModel(0, 3, parent);

     model->setHeaderData(0, Qt::Horizontal, QObject::tr("Subject"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("Sender"));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date"));

     addMail(model, "Re: Expenses", "Andy <andy@nospam.com>",
             QDateTime(QDate(2007, 01, 02), QTime(16, 05)));
     addMail(model, "Re: Accounts", "Andy2 <andy2@nospam.com>",
             QDateTime(QDate(2007, 01, 03), QTime(14, 26)));

     return model;
 }

 int main(int argc, char *argv[])
 {
     QApplication app(argc, argv);
     Window window;
     window.setSourceModel(createMailModel(&window));
     window.show();
     return app.exec();
 }
