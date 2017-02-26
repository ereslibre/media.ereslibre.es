#ifndef KPARTTUTORIAL1_H
#define KPARTTUTORIAL1_H
 
#include <kparts/mainwindow.h>
 
class MainWindow
    : public KParts::MainWindow
{
    Q_OBJECT

public:
    MainWindow();
     virtual ~MainWindow();

    void load(const KUrl& url);

public Q_SLOTS:
    void fileOpen();

private:
    void setupActions();

private:
    KParts::ReadOnlyPart *m_part;
};
 
#endif // KPARTTUT1_H
