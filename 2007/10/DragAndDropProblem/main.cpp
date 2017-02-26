/**
 * Code example created by Rafael Fernández López <ereslibre@kde.org>
 * This code is licensed under the terms of the General Public License v2 or more.
 */

#include <QApplication>
#include <QTreeView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QWidget>
#include <QBoxLayout>
#include <QHeaderView>
#include <QScrollBar>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  QWidget *widget = new QWidget();
  QVBoxLayout *layout = new QVBoxLayout;

  widget->setLayout(layout);

  QTreeView *treeView = new QTreeView(widget);
  treeView->setDragDropMode(QTreeView::DragOnly);
  treeView->setSelectionMode(QTreeView::ExtendedSelection);
  treeView->header()->setVisible(false);
  treeView->setRootIsDecorated(false);

  QStandardItemModel *model = new QStandardItemModel();
  model->insertColumn(0);
  for (int i = 0; i < 100; ++i)
  {
    model->insertRow(i);
    model->setData(model->index(i, 0), QString("Element ") + QString::number(i + 1), Qt::DisplayRole);
  }

  treeView->setModel(model);

  layout->addWidget(treeView);

  widget->show();

  return app.exec();
}
