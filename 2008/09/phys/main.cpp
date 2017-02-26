#include "surface.h"
#include "mass.h"

#include <QtCore/QTime>

#include <QtGui/QApplication>
#include <QtGui/QGraphicsView>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    srandom(QTime::currentTime().msec());

    QGraphicsView *view = new QGraphicsView;
    view->setResizeAnchor(QGraphicsView::NoAnchor);
    view->setRenderHint(QPainter::Antialiasing);
    Surface *surface = new Surface(view);
    view->setScene(surface);

    for (int i = 0; i < 5; ++i) {
        Mass *mass = new Mass(0, surface);
    }

    view->showMaximized();

    return app.exec();
}
