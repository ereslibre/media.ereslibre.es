#include <QApplication>
#include <QMainWindow>
#include <QToolBar>

int main( int argc,  char **argv )
{
QApplication app( argc,  argv );
QMainWindow *mainWindow = new QMainWindow();
mainWindow->setCentralWidget( new QWidget( mainWindow ) );
QToolBar *a = new QToolBar( "a",  mainWindow );
QToolBar *b = new QToolBar( "b",  mainWindow );
a->setObjectName( "a" );
b->setObjectName( "b" );
a->addAction( "Test" );
a->addAction( "Test2" );
b->addAction( "Test3" );
b->addAction( "Test4" );
mainWindow->addToolBar( a );
mainWindow->addToolBar( b );
QByteArray state = mainWindow->saveState();
mainWindow->restoreState(state);
mainWindow->show();
return app.exec();
}
