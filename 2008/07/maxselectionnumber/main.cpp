#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QStringListModel>
#include <QtGui/QItemSelectionModel>
#include <QDebug>

#define MAX_SELECTIONS 5

class MySelectionModel
    : public QItemSelectionModel
{
public:
    MySelectionModel(QAbstractItemModel *parent = 0)
        : QItemSelectionModel(parent)
    {
    }

    virtual void select(const QItemSelection &selection, QItemSelectionModel::SelectionFlags command)
    {
        if (selectedIndexes().count() < MAX_SELECTIONS) {
            QItemSelectionModel::select(selection, command);
        }
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow *mainWindow = new QMainWindow();

    QStringListModel *model = new QStringListModel(mainWindow);

    model->insertRows(0, 100);
    for (int i = 0; i < 100; ++i) {
        model->setData(model->index(i, 0), "Test");
    }

    QListView *listView = new QListView(mainWindow);
    listView->setSelectionMode(QListView::ExtendedSelection);
    listView->setModel(model);
    listView->setSelectionModel(new MySelectionModel(model));

    mainWindow->setCentralWidget(listView);
    mainWindow->show();

    return app.exec();
}
