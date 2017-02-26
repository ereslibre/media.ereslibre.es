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

signals:
  void mySignal() const;
};

int main(int argc, char **argv)
{
  QApplication app(argc, argv);

  MyObject obj;
  obj.mySlot();

  return app.exec();
}

#include "main.moc"

