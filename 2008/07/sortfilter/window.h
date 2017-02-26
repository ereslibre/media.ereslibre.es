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

 #ifndef WINDOW_H
 #define WINDOW_H

 #include <QWidget>

 class QAbstractItemModel;
 class QCheckBox;
 class QComboBox;
 class QGroupBox;
 class QLabel;
 class QLineEdit;
 class QSortFilterProxyModel;
 class QTreeView;

 class Window : public QWidget
 {
     Q_OBJECT

 public:
     Window();

     void setSourceModel(QAbstractItemModel *model);

 private slots:
     void filterRegExpChanged();
     void filterColumnChanged();
     void sortChanged();

 private:
     QSortFilterProxyModel *proxyModel;

     QGroupBox *sourceGroupBox;
     QGroupBox *proxyGroupBox;
     QTreeView *sourceView;
     QTreeView *proxyView;
     QCheckBox *filterCaseSensitivityCheckBox;
     QCheckBox *sortCaseSensitivityCheckBox;
     QLabel *filterPatternLabel;
     QLabel *filterSyntaxLabel;
     QLabel *filterColumnLabel;
     QLineEdit *filterPatternLineEdit;
     QComboBox *filterSyntaxComboBox;
     QComboBox *filterColumnComboBox;
 };

 #endif
