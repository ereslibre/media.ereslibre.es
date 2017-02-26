/***
  * Copyright 2008 (C) Rafael Fernández López <ereslibre@kde.org>
  *
  * This code is GPL v2 or more.
  *
  * Hey, I know the code sucks a bit at some points, but is nice, and gonna get nicer :)
  */

#include <math.h>

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QToolBar>
#include <QAction>
#include <QLabel>

class Vector2D
{
public:
    Vector2D(float x, float y)
        : x(x)
        , y(y)
    {
    }

    float module()
    {
        return sqrt(x * x + y * y);
    }

    Vector2D normalize()
    {
        float m = module();
        return Vector2D(x / m, y / m);
    }

public:
    float x;
    float y;
};

class Mass
    : public QGraphicsItem
    , public QObject
{
public:
    Mass(float x, float y, bool fixed = false, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
        : QGraphicsItem(parent, scene)
        , QObject(0)
        , position(new Vector2D(x, y))
        , force(new Vector2D(0, 0))
        , airFriction(0.98)
        , floorFriction(0.9)
        , selected(false)
        , fixed(fixed)
    {
        id = startTimer(10);
        setZValue(1);
        setPos(x, y);
        setFlag(QGraphicsItem::ItemIsMovable);
    }

    ~Mass()
    {
        delete position;
        delete force;
    }

    QRectF boundingRect() const
    {
        return QRectF(-5, -5, 10, 10);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)
    {
        painter->setRenderHint(QPainter::Antialiasing);

        painter->save();
        QLinearGradient g(QPointF(0, -5), QPointF(0, 5));
        g.setColorAt(0, Qt::yellow);
        g.setColorAt(1, Qt::white);
        painter->setBrush(g);
        painter->drawEllipse(option->rect);
        painter->restore();
    }

    void updatePos()
    {
        position->x += force->x;
        position->y += force->y;

        setPos(position->x, position->y);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        selected = true;
        position->x = scenePos().x();
        position->y = scenePos().y();

        QGraphicsItem::mousePressEvent(event);
    }

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
        position->x = scenePos().x();
        position->y = scenePos().y();

        scene()->update(scene()->sceneRect());

        QGraphicsItem::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
    {
        selected = false;
        position->x = scenePos().x();
        position->y = scenePos().y();

        QGraphicsItem::mouseReleaseEvent(event);
    }

    void timerEvent(QTimerEvent *event)
    {
        if (!fixed && !selected)
        {
            if (position->y > 350)
            {
                position->y = 350;
                force->y *= floorFriction;

                if (force->y > 0)
                {
                    force->y = - force->y * floorFriction;
                }
            }

            force->y += 0.4;
            force->x *= airFriction;
            force->y *= airFriction;

            updatePos();
        }

        scene()->update(scene()->sceneRect());
    }

public:
    Vector2D *position;
    Vector2D *force;
    float airFriction;
    float floorFriction;
    bool fixed;
    int id;
#if 1
    bool selected;
#endif
};

class Spring
    : public QGraphicsItem
    , public QObject
{
public:
    Spring(Mass *a, Mass *b, float length, QGraphicsItem *parent = 0, QGraphicsScene *scene = 0)
        : QGraphicsItem(parent, scene)
        , QObject(0)
        , a(a)
        , b(b)
        , length(length)
        , damp(0.1)
        , k(0.5)
        , ticks(0)
    {
        //startTimer(100);
        setZValue(0);
    }

    QRectF boundingRect() const
    {
        QPointF topLeft(qMin(a->position->x, b->position->x),
                        qMin(a->position->y, b->position->y));

        QPointF bottomRight(qMax(a->position->x, b->position->x),
                            qMax(a->position->y, b->position->y));

        return QRectF(topLeft, bottomRight);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)
    {
        painter->setRenderHint(QPainter::Antialiasing);

        painter->save();
        painter->setPen(Qt::red);
        painter->drawLine(a->position->x, a->position->y, b->position->x, b->position->y);
        painter->restore();
    }

protected:
    void timerEvent(QTimerEvent *event)
    {
        if (!ticks)
        {
            if (!a->fixed && !a->selected)
            {
                Vector2D vel(a->force->x - b->force->x, a->force->y - b->force->y);
                Vector2D d(a->position->x - b->position->x, a->position->y - b->position->y);
                Vector2D nd = d.normalize();
                //a->force->x += -k * (abs(d.x) - abs(nd.x * length)) * nd.x - damp * vel.x;
                a->force->y += -k * (abs(d.y) - abs(nd.y * length)) * nd.y - damp * vel.y;
            }

            if (!b->fixed && !b->selected)
            {
                Vector2D vel(b->force->x - b->force->x, b->force->y - b->force->y);
                Vector2D d(b->position->x - b->position->x, b->position->y - b->position->y);
                Vector2D nd = d.normalize();
                //b->force->x += -k * (abs(d.x) - abs(nd.x * length)) * nd.x - damp * vel.x;
                b->force->y += -k * (abs(d.y) - abs(nd.y * length)) * nd.y - damp * vel.y;
            }

            ticks++;
        }
    }

public:
    Mass *a;
    Mass *b;
    float length;
    float damp;
    float k;
    int ticks;
};

int gravity = 10;
QGraphicsScene *graphicsScene = 0;
QAction *less = 0;
QAction *more = 0;

class Handler
    : public QObject
{
    Q_OBJECT

public:
    Handler()
        : QObject()
    {
    }

public Q_SLOTS:
    void lessGravity()
    {
        if (gravity == 5)
            more->setEnabled(true);

        gravity += 5;

        foreach (QGraphicsItem *item, graphicsScene->items())
        {
            QObject *objItem = dynamic_cast<QObject*>(item);
            Mass *massItem = dynamic_cast<Mass*>(item);

            if (massItem)
            {
                objItem->killTimer(massItem->id);
                massItem->id = objItem->startTimer(gravity);
            }
        }
    }

    void moreGravity()
    {
        gravity -= 5;

        foreach (QGraphicsItem *item, graphicsScene->items())
        {
            QObject *objItem = dynamic_cast<QObject*>(item);
            Mass *massItem = dynamic_cast<Mass*>(item);

            if (massItem)
            {
                objItem->killTimer(massItem->id);
                massItem->id = objItem->startTimer(gravity);
            }
        }

        if (gravity == 5)
            more->setEnabled(false);
    }
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QMainWindow *mainWindow = new QMainWindow();
    QGraphicsView *graphicsView = new QGraphicsView(mainWindow);
    graphicsScene = new QGraphicsScene(mainWindow);

    graphicsView->setScene(graphicsScene);

    Mass *m1 = new Mass(50, 100);
    //Mass *m2 = new Mass(10, 100, true);
    //Mass *m3 = new Mass(90, 100, true);
    Mass *m2 = new Mass(10, 100);
    Mass *m3 = new Mass(90, 100);
    graphicsScene->addItem(m1);
    graphicsScene->addItem(m2);
    graphicsScene->addItem(m3);
    graphicsScene->addItem(new Spring(m1, m2, 10));
    graphicsScene->addItem(new Spring(m1, m3, 10));

    graphicsView->setResizeAnchor(QGraphicsView::NoAnchor);

    mainWindow->setCentralWidget(graphicsView);
    mainWindow->setGeometry(QRect(0, 0, 800, 600));

    QToolBar *toolBar = new QToolBar("mainToolBar", mainWindow);
    less = toolBar->addAction("Less Gravity");
    more = toolBar->addAction("More Gravity");
    toolBar->addSeparator();
    toolBar->addWidget(new QLabel("ereslibre@kde.org"));

    Handler *handler = new Handler();

    QObject::connect(less, SIGNAL(triggered(bool)), handler, SLOT(lessGravity()));
    QObject::connect(more, SIGNAL(triggered(bool)), handler, SLOT(moreGravity()));

    mainWindow->addToolBar(toolBar);

    mainWindow->show();

    return app.exec();
}

#include "main.moc"

