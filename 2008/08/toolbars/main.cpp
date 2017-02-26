#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QSettings>
#include <QObject>
#include <QAction>

class Listener
    : public QObject
{
Q_OBJECT

public:
    Listener(QMainWindow *window)
        : QObject(window)
        , mWindow(window)
    {
    }

    ~Listener()
    {
    }

public slots:
    void slotTriggered()
    {
        QSettings settings("settings.txt");
        QByteArray state = mWindow->saveState();
        settings.setValue("state", state);
    }

private:
    QMainWindow *mWindow;
};

int main( int argc,  char **argv )
{
    QApplication app( argc,  argv );
    QMainWindow *mainWindow = new QMainWindow();
    Listener *listener = new Listener(mainWindow);
    mainWindow->setCentralWidget( new QWidget( mainWindow ) );
    QToolBar *a = new QToolBar( "a",  mainWindow );
    QToolBar *b = new QToolBar( "b",  mainWindow );
    a->setObjectName( "a" );
    b->setObjectName( "b" );
    a->addAction( "Test" );
    a->addAction( "Test2" );
    b->addAction( "Test3" );
    QAction *action = b->addAction( "Save State" );
    QObject::connect(action, SIGNAL(triggered()), listener, SLOT(slotTriggered()));
    mainWindow->addToolBar( a );
    mainWindow->addToolBar( b );
    QSettings settings("settings.txt");
    QByteArray state = settings.value("state").toByteArray();
    mainWindow->restoreState(state);
    a->addAction( "Test Action" );
    a->addAction( "Another Test" );
    mainWindow->show();
    return app.exec();
}

#include "main.moc"
