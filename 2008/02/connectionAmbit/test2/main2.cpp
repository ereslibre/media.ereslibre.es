#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtGui/QApplication>

class A
    : public QObject
{
    Q_OBJECT

public:
    A()
    {
        connect(this, SIGNAL(signalA()), SLOT(debugMe()));
    }

Q_SIGNALS:
    void signalA();

private Q_SLOTS:
    void debugMe()
    {
        qDebug() << "SIGNAL A WAS EMITTED";
    }
};

class B
    : public QObject
{
    Q_OBJECT

public:
    void tachan()
    {
        connect(this, SIGNAL(signalB()), new A(), SIGNAL(signalA()));
        signalB();
    }

Q_SIGNALS:
    void signalB();
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    B *b = new B();
    b->tachan();

    return app.exec();
}

#include "main2.moc"
