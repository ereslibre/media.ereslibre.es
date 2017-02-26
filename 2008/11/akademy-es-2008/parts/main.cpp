#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>
 
#include "mainwindow.h"
 
int main (int argc, char *argv[])
{
    KAboutData aboutData( "visorglobal", "visorglobal",
        ki18n("Un visor global"), "0.1",
        ki18n("Un visor global"),
        KAboutData::License_GPL,
        ki18n("Copyright (c) 2008 Rafael Fernández López") );
    KCmdLineArgs::init( argc, argv, &aboutData );

    KCmdLineOptions options;
    options.add("+[file]", ki18n("Document to open"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;

    MainWindow* window = new MainWindow();

    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
    if(args->count())
    {
        window->load(args->url(0).url());
    }

    window->show();

    return app.exec();
}
