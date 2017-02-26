#include <QApplication>
#include <QObject>
#include <QDebug>

class MyObject
  : public QObject
{
  Q_OBJECT

public:
  MyObject(QObject *parent = 0)
    : QObject(parent)
  {
    connect(this, SIGNAL(mySignal()), this, SLOT(calledSlot()));
    connect(this, SIGNAL(mySignal()), this, SIGNAL(myOtherSignal()));
    connect(this, SIGNAL(myOtherSignal()), this, SLOT(myOtherCalledSlot()));
  }

  ~MyObject() { }

public slots:
  void mySlot() const
  {
    emit mySignal();
  }

  void calledSlot() const
  {
    qDebug() << "HEY, I WAS FINALLY CALLED";
  }

  void myOtherCalledSlot()
  {
    qDebug() << "HEY, I WAS FINALLY CALLED (ME TOO), AND THIS WAS REALLY AMAZING";
  }

signals:
  void mySignal() const;
  void myOtherSignal();
};

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  MyObject obj;
  obj.mySlot();

  return app.exec();
}

#include "main.moc"

