#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QPushButton>
#include <QIcon>

class NewClass
    : public QObject
{
    Q_OBJECT

public:
    NewClass(QObject *parent = 0)
        : QObject(parent)
        , toolBar(new QToolBar("maintoolbar"))
    {
        a = false;
    }

    ~NewClass()
    {
    }

public Q_SLOTS:
    void slotClick()
    {
        if (a)
            toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);
        else
            toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        a = !a;
    }

public:
    QToolBar *toolBar;
    bool a;
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow *main = new QMainWindow();

    NewClass *newClass = new NewClass(main);
newClass->toolBar->setParent(main);

    QPushButton *pushButton = new QPushButton("Push here", main);
    main->setCentralWidget(pushButton);

    QObject::connect(pushButton, SIGNAL(clicked(bool)), newClass, SLOT(slotClick()));


    newClass->toolBar->addAction(QIcon("/home/ereslibre/kde/share/icons/oxygen/48x48/apps/knotes.png"), "New Document");
    newClass->toolBar->addAction(QIcon("/home/ereslibre/kde/share/icons/oxygen/48x48/apps/knotes.png"), "Open Document");
    newClass->toolBar->addAction(QIcon("/home/ereslibre/kde/share/icons/oxygen/48x48/apps/knotes.png"), "Save Document");
    newClass->toolBar->addAction(QIcon("/home/ereslibre/kde/share/icons/oxygen/48x48/apps/knotes.png"), "Close Document");

    main->addToolBar(newClass->toolBar);

    newClass->toolBar->setToolButtonStyle(Qt::ToolButtonIconOnly);

    main->show();

    return app.exec();
}

#include "main.moc"
