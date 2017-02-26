#include <QApplication>
#include <QListView>
#include <QStringListModel>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QStringListModel *model = new QStringListModel();
    model->insertRows(0, 5);
    for (int i = 0; i < 5; ++i) {
        model->setData(model->index(i, 0), "Row " + QString::number(i), Qt::DisplayRole);
    }

    QListView *view = new QListView();
    view->setSelectionMode(QListView::SingleSelection);
    view->setModel(model);

    view->show();

    return app.exec();
}
