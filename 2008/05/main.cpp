#include <QApplication>
#include <QPaintEvent>
#include <QPushButton>
#include <QPainter>
#include <QWidget>

class MyWidget
    : public QWidget
{
public:
    MyWidget(QWidget *parent = 0)
        : QWidget(parent)
        , pushButton(new QPushButton)
    {
        pushButton->setText("Click me");
    }

    ~MyWidget()
    {
    }

protected:
    virtual void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        p.fillRect(event->rect(), Qt::white);
        p.end();
        pushButton->render(this, QPoint(0, 0), QRegion(QRect(QPoint(0, 0), pushButton->sizeHint())), QWidget::DrawChildren);
    }

private:
    QPushButton *pushButton;
};

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MyWidget *myWidget = new MyWidget;
    myWidget->show();

    return app.exec();
}
