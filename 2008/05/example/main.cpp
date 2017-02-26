#include <QApplication>
#include <QTreeView>
#include <QDirModel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QDirModel *model = new QDirModel;

    QTreeView *treeView = new QTreeView();
    treeView->setHeaderHidden(true);
    treeView->setModel(model);
    treeView->setColumnHidden(1, true);
    treeView->setColumnHidden(2, true);
    treeView->setColumnHidden(3, true);

    treeView->show();

    return app.exec();
}
