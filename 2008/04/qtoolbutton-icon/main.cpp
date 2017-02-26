#include <QApplication>
#include <QToolButton>
#include <QMainWindow>
#include <QPushButton>
#include <QMenu>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);


    // Non-parented tool button. No icon is drawn.
    QToolButton *toolButton = new QToolButton();
    toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton->setText("This is a non-parented QToolButton");
    toolButton->setIcon(QPixmap("kde.png"));
    toolButton->show();

    // Parented tool button. The icon is drawn.
    QMainWindow *mainWindow = new QMainWindow();
    QToolButton *toolButton2 = new QToolButton(mainWindow);
    toolButton2->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    toolButton2->setText("This is a parented QToolButton");
    toolButton2->setIcon(QPixmap("kde.png"));
    mainWindow->setCentralWidget(toolButton2);
    mainWindow->show();

    // As an example of working correctly, QPushButton can handle
    // icons normally on non-parented widgets.
    QPushButton *pushButton = new QPushButton();
    pushButton->setText("This is a non-parented QPushButton");
    pushButton->setIcon(QPixmap("kde.png"));
    pushButton->show();

    return app.exec();
}
