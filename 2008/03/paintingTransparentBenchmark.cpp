#include <qglobal.h>
#include <QtGui>

int main(int argc, char** argv)
{
  QApplication a(argc, argv);
  QPixmap pm(300, 300);
  int iter = 200;
  qDebug() << "Iterating" << iter << "times.";
  QTime t;
  t.start();
  QRect sub(0,0,50,50);
  for (int i=0 ; i < iter ; i++) {
    pm.fill( Qt::transparent );    
  }
  qDebug() << "fill pixmap:" << t.restart() << "ms";
  QPainter p;
  for (int i=0 ; i < iter ; i++) {
    pm.setMask(pm.createMaskFromColor(Qt::transparent, Qt::MaskOutColor));
  }  
  qDebug() << "set mask:" << t.restart() << "ms";
  for (int i=0 ; i < iter ; i++) {
      p.begin(&pm);
      p.setCompositionMode( QPainter::CompositionMode_Source );
      p.fillRect(sub, Qt::transparent);
      p.end();
  }
  qDebug() << "fillRect + CompositionMode_Source:" << t.restart() << "ms";
  qDebug("using Qt %s", QT_VERSION_STR);
  exit(0);
}
