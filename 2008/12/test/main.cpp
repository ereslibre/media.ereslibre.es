#include <QTest>
#include <QSignalSpy>
#include <QLineEdit>

class MyLineEdit
    : public QLineEdit
{
public:
    MyLineEdit(QWidget *parent = 0)
        : QLineEdit(parent)
        , keyPress(0)
        , keyRelease(0)
    {
    }

    ~MyLineEdit()
    {
    }

protected:
    void keyPressEvent(QKeyEvent *event)
    {
        QLineEdit::keyPressEvent(event);
        keyPress++;
    }

    void keyReleaseEvent(QKeyEvent *event)
    {
        QLineEdit::keyReleaseEvent(event);
        keyRelease++;
    }

public:
    int keyPress;
    int keyRelease;
};

class MainClass
    : public QObject
{
    Q_OBJECT

public:
    MainClass(QObject *parent = 0)
        : QObject(parent)
        , lineEdit(new MyLineEdit)
    {
    }

    ~MainClass()
    {
    }

private Q_SLOTS:
    void testLineEditBasic()
    {
        QSignalSpy spy(lineEdit, SIGNAL(textEdited(QString)));
        QTest::keyClicks(lineEdit, "tést");
        QCOMPARE(spy.count(), 5);
    }

    void testLineEditPresses()
    {
        lineEdit->keyPress = 0;
        QTest::keyClicks(lineEdit, "tést");
        QCOMPARE(lineEdit->keyPress, 5);
    }

    void testLineEditReleases()
    {
        lineEdit->keyRelease = 0;
        QTest::keyClicks(lineEdit, "tést");
        QCOMPARE(lineEdit->keyRelease, 5);
    }

private:
    MyLineEdit *lineEdit;
};

QTEST_MAIN(MainClass)

#include "main.moc"
