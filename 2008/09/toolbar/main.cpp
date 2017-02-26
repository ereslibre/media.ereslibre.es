#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QSettings>
#include <QObject>
#include <QAction>
#include <QLineEdit>

int main( int argc,  char **argv )
{
    QApplication app( argc,  argv );
    QMainWindow *mainWindow = new QMainWindow();
    mainWindow->setCentralWidget( new QWidget( mainWindow ) );
    QToolBar *a = new QToolBar( "a", mainWindow );
    QToolBar *b = new QToolBar( "b", mainWindow );
    a->addAction( "Test" );
    b->addWidget(new QLineEdit(mainWindow));
    mainWindow->addToolBar( a );
    mainWindow->addToolBar( b );
    mainWindow->show();
    return app.exec();
}
