#include "goya.h"

#include <kdebug.h>

#include <QWidget>
#include <QPainter>
#include <QListView>
#include <QBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QStringListModel>

class MiModel
    : public QStringListModel
{
    Q_OBJECT

public:
    MiModel(QAbstractItemView *itemView, QObject *parent = 0)
        : QStringListModel(parent)
        , itemView(itemView)
    {
        button = new Goya::PushButton();
        button2 = new Goya::PushButton();

        opt = new QStyleOptionButton();
        opt2 = new QStyleOptionButton();

        button2->setEatEvents(true);

        connect(button, SIGNAL(clicked(QModelIndex)), this, SLOT(slotClicked1(QModelIndex)));
        connect(button2, SIGNAL(clicked(QModelIndex)), this, SLOT(slotClicked2(QModelIndex)));
    }

    virtual ~MiModel()
    {
        delete button;
        delete button2;
        delete opt;
        delete opt2;
    }

    QVariant data(const QModelIndex &index, int role) const
    {
        if (role == Goya::WidgetStyleRole)
        {
            opt->initFrom(itemView);
            opt2->initFrom(itemView);

            opt->rect = QRect(25, 25, 200, 50);
            opt->text = QString("Left button test ") + QString::number(index.row() + 1);

            opt2->rect = QRect(250, 25, 200, 50);
            opt2->text = QString("Right button test ") + QString::number(index.row() + 1);

            if (index.row() % 2)
            {
                return QVariant::fromValue(QList<QStyleOption*>() << opt << opt2);
            }
            else if (index.row() % 3)
            {
                return QVariant::fromValue(QList<QStyleOption*>() << opt2);
            }

            return QVariant::fromValue(QList<QStyleOption*>());
        }
        else if (role == Goya::WidgetRole)
        {
            if (index.row() % 2)
            {
                return QVariant::fromValue(QList<Goya::Widget*>() << button << button2);
            }
            else if (index.row() % 3)
            {
                return QVariant::fromValue(QList<Goya::Widget*>() << button2);
            }

            return QVariant::fromValue(QList<Goya::Widget*>());
        }

        return QStringListModel::data(index, role);
    }

private:
    Goya::PushButton *button;
    Goya::PushButton *button2;
    QStyleOptionButton *opt;
    QStyleOptionButton *opt2;
    QAbstractItemView *itemView;

private Q_SLOTS:
    void slotClicked1(const QModelIndex &index)
    {
        //qDebug() << "GOYA LEFT BUTTON CLICKED ON INDEX ROW " << index.row() + 1 << endl;
        QMessageBox::information(0, "Button clicked", "Goya LEFT button clicked on index row " + QString::number(index.row() + 1));
    }

    void slotClicked2(const QModelIndex &index)
    {
        //qDebug() << "GOYA RIGHT BUTTON CLICKED ON INDEX ROW " << index.row() + 1 << endl;
        QMessageBox::information(0, "Button clicked", "Goya RIGHT button clicked on index row " + QString::number(index.row() + 1));
    }
};

class MiDelegate
    : public Goya::Canvas
{
public:
    MiDelegate(QAbstractItemView *itemView, QObject *parent = 0)
        : Canvas(itemView, parent)
    {
    }

    virtual ~MiDelegate()
    {
    }

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const
    {
        if (option.state & QStyle::State_Selected)
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }

        Canvas::paint(painter, option, index);
    }

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const
    {
        Q_UNUSED(index);

        return QSize(100, 100);
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout;

    widget->setLayout(layout);
    widget->resize(800, 600);

    QListView *listView = new QListView();
    MiDelegate *delegate = new MiDelegate(listView);
    MiModel *model = new MiModel(listView);

    model->insertColumn(0);
    for (int i = 0; i < 50; ++i)
    {
        model->insertRow(i);
        model->setData(model->index(i, 0), QString::number(i));
    }

    listView->setModel(model);
    listView->setItemDelegate(delegate);
    listView->setVerticalScrollMode(QListView::ScrollPerPixel);

    layout->addWidget(listView);

    widget->show();

    return app.exec();
}

#include "main.moc"
