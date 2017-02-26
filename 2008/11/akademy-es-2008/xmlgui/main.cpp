#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>

#include "mainwindow.h"

int main (int argc, char *argv[])
{
    KAboutData aboutData("ejemploxmlgui", "ejemploxmlgui",
                         ki18n("ejemploxmlgui"), "1.0",
                         ki18n("Un ejemplo de xmlgui"),
                         KAboutData::License_GPL,
                         ki18n("Copyright (c) 2008 Rafael Fernández López"));
    KCmdLineArgs::init(argc, argv, &aboutData);
    KApplication app;
    MainWindow *window = new MainWindow();
    window->show();
    return app.exec();
}
