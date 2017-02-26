#include "mainwindow.h"

#include <QtCore/QTimer>

#include <kaction.h>
#include <kactioncollection.h>
#include <kconfig.h>
#include <kedittoolbar.h>
#include <kfiledialog.h>
#include <kshortcutsdialog.h>
#include <klibloader.h>
#include <kmessagebox.h>
#include <kstandardaction.h>
#include <kstatusbar.h>
#include <kurl.h>
#include <kservice.h>
#include <kmimetypetrader.h>
#include <kapplication.h>

MainWindow::MainWindow()
    : KParts::MainWindow( )
{
    setupActions();
}

MainWindow::~MainWindow()
{
    if (m_part) {
        m_part->closeUrl();
    }
}

void MainWindow::load(const KUrl& url)
{
    KMimeType::Ptr mime = KMimeType::findByUrl(url);
    m_part = KMimeTypeTrader::self()->createPartInstanceFromQuery<KParts::ReadWritePart>(mime->name());
    if (!m_part) {
        m_part = KMimeTypeTrader::self()->createPartInstanceFromQuery<KParts::ReadOnlyPart>(mime->name());
    }
    if (m_part) {
        setCentralWidget(m_part->widget());
        createGUI(m_part);
        setupGUI(ToolBar | Keys | StatusBar | Save);
        m_part->openUrl(url);
    } else {
        KMessageBox::error(this, "Could not find our Part!");
        QTimer::singleShot(0, kapp, SLOT(quit()));
    }
}
 
void MainWindow::setupActions()
{
}
