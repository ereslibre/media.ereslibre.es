#include <QLineEdit>
#include <QDebug>
#include <QApplication>

class MyLineEdit
    : public QLineEdit
{
public:
    MyLineEdit(QWidget *parent = 0)
        : QLineEdit(parent)
    {
    }

    ~MyLineEdit()
    {
    }

protected:
    void keyPressEvent(QKeyEvent *event)
    {
        QLineEdit::keyPressEvent(event);
        qDebug() << "key press";
    }

    void keyReleaseEvent(QKeyEvent *event)
    {
        QLineEdit::keyReleaseEvent(event);
        qDebug() << "key release";
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyLineEdit *lineEdit = new MyLineEdit;
    lineEdit->show();

    return app.exec();
}
