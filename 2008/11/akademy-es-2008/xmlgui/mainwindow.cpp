#include "mainwindow.h"

#include <KApplication>
#include <KAction>
#include <KLocale>
#include <KActionCollection>
#include <KStandardAction>

MainWindow::MainWindow(QWidget *parent)
    : KXmlGuiWindow(parent)
{
    textArea = new KTextEdit;
    setCentralWidget(textArea);
    setupActions();
}

void MainWindow::setupActions()
{
    KStandardAction::open(kapp, SLOT(quit()), actionCollection());
    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
    setupGUI();
}
