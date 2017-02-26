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
    : KParts::MainWindow()
    , m_part(0)
{
    setupActions();
    setupGUI();
    setAutoSaveSettings();
}

MainWindow::~MainWindow()
{
    if (m_part) {
        m_part->closeUrl();
    }
    delete m_part;
}

void MainWindow::load(const KUrl& url)
{
    if (m_part) {
        m_part->closeUrl();
    }
    delete m_part;

    KMimeType::Ptr mime = KMimeType::findByUrl(url);
    m_part = KMimeTypeTrader::self()->createPartInstanceFromQuery<KParts::ReadWritePart>(mime->name());
    if (!m_part) {
        m_part = KMimeTypeTrader::self()->createPartInstanceFromQuery<KParts::ReadOnlyPart>(mime->name());
    }
    if (m_part) {
        setCentralWidget(m_part->widget());
        createGUI(m_part);
        m_part->openUrl(url);
    } else {
        KMessageBox::error(this, "Could not find our Part!");
        QTimer::singleShot(0, kapp, SLOT(quit()));
    }
}

void MainWindow::fileOpen()
{
    const QString url = KFileDialog::getOpenFileName();
    if (!url.isEmpty()) {
        load(url);
    }
}

void MainWindow::setupActions()
{
    KStandardAction::open(this, SLOT(fileOpen()), actionCollection());
    KStandardAction::quit(kapp, SLOT(quit()), actionCollection());
}

#include "mainwindow.moc"
