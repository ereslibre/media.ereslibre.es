#include <QString>
#include <QApplication>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QBoxLayout>

class MiWidget
    : public QWidget
{
public:
    MiWidget(int count, const QString &filename)
    {
        m_count = count;
        m_filename = filename;
    }
    
    virtual QSize minimumSizeHint() const
    {
        QPixmap pm(QString("%1.png").arg(m_filename));
        return QSize(pm.width(), pm.height() + fontMetrics().height());
    }

protected:
    virtual void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);
        
        if (!m_count) {
            QSvgRenderer renderer(QString("%1.svg").arg(m_filename));
            renderer.render(&p, QRect(0, 0, event->rect().width(), event->rect().height() - fontMetrics().height()));
            p.drawText(event->rect(), Qt::AlignBottom | Qt::AlignHCenter, "SVG version");
        } else {
            QPixmap pm(QString("%1.png").arg(m_filename));
            p.drawPixmap(event->rect().width() / 2 - pm.width() / 2, 0, pm);
            p.drawText(event->rect(), Qt::AlignBottom | Qt::AlignHCenter, "PNG version");
        }

        p.end();
    }

private:
    QString m_filename;
    int m_count;
};

int main (int argc, char *argv[])
{
    if (argc == 1) {
        return 0;
    }

    QApplication app(argc, argv);

    QWidget *mainWidget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;
    mainWidget->setLayout(layout);
    layout->addWidget(new MiWidget(0, QString(argv[1])));
    layout->addWidget(new MiWidget(1, QString(argv[1])));
    mainWidget->show();

    return app.exec();
}
