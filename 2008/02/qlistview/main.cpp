#include <QtGui/QApplication>
#include <QtGui/QMainWindow>
#include <QtGui/QListView>
#include <QtGui/QStringListModel>

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
    listView->setViewMode(QListView::IconMode);
    listView->setModel(model);

    mainWindow->setCentralWidget(listView);
    mainWindow->show();

    return app.exec();
}
