#include <QApplication>
#include <QStringListModel>
#include <QHash>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QHash<QPersistentModelIndex, int> hash;

    QStringListModel *model = new QStringListModel();

    model->insertRow(0);
    const QModelIndex index = model->index(0, 0);
    QPersistentModelIndex persistent(index);
    model->setData(index, "b");

    hash[index]; // add the index to the hash

    model->insertRow(1);
    const QModelIndex index2 = model->index(1, 0);
    model->setData(index2, "a");

    model->sort(0);

    Q_ASSERT(hash.keys().contains(persistent)); // passes !
    Q_ASSERT(hash.contains(persistent)); // fails !
}
