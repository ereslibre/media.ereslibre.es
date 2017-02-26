#include <QString>
#include <KApplication>
#include <KAboutData>
#include <KMessageBox>
#include <KCmdLineArgs>
#include <KLocalizedString>
#include <kiconloader.h>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class MiWidget
    : public QWidget
{
protected:
    virtual void paintEvent(QPaintEvent *event)
    {
        QPainter p(this);

        p.drawPixmap(event->rect().width() / 2 - qMin(event->rect().height(), event->rect().width()) / 2,
                     event->rect().height() / 2 - qMin(event->rect().height(), event->rect().width()) / 2,
                     KIconLoader::global()->loadIcon("start-here", KIconLoader::NoGroup, qMin(event->rect().height(), event->rect().width())));

        p.end();
    }
};

int main (int argc, char *argv[])
{
    KAboutData aboutData("tutorial1",                  // The program name used internally.
                         0,                            // The message catalog name, use program name if null.
                         ki18n("Tutorial 1"),          // A displayable program name string.
                         "1.0",                        // The program version string.
                         ki18n("KMessageBox popup"),   // A short description of what the program does.
                         KAboutData::License_GPL,      // License identifier
                         ki18n("(c) 2007"),            // Copyright Statement
                         ki18n("Some text..."),        // Some free form text, that can contain any kind of information.
                         "http://tutorial.com",        // The program homepage string.
                         "submit@bugs.kde.org");       // The bug report email address string.

    KCmdLineArgs::init( argc, argv, &aboutData );
    KApplication app;

    MiWidget *widget = new MiWidget();
    widget->show();

    return app.exec();
}
