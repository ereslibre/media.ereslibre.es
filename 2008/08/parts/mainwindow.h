#ifndef KPARTTUTORIAL1_H
#define KPARTTUTORIAL1_H
 
#include <kparts/mainwindow.h>
 
class MainWindow : public KParts::MainWindow
{
public:
    MainWindow();
     virtual ~MainWindow();
 
    void load(const KUrl& url);
 
private:
    void setupActions();
 
private:
    KParts::ReadOnlyPart *m_part;
};
 
#endif // KPARTTUT1_H
