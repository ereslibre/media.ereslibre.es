#include <QList>
#include <QString>
#include <QHash>

#include <iostream>

using namespace std;
class Button;

template <class P1>
class Callback1Base
{
public:
    virtual void operator()(P1) const = 0;
    virtual Callback1Base<P1> *clone() const = 0;

    template <class Client, class Member>
    static Callback1Base<P1> *make(Client &client_, Member member_);
};

template <class P1, class Client, class Member>
class Callback1
    : public Callback1Base<P1>
{
public:
    Callback1(Client &client_, Member member_)
        : _client(client_)
        , _member(member_)
    {
    }

    virtual void operator()(P1 parm_) const
    {
        ((&_client)->*_member)(parm_);
    }

    virtual Callback1<P1, Client, Member> *clone() const
    {
        return new Callback1<P1, Client, Member>(*this);
    }

private:
    Client &_client;
    Member _member;
};

template <class P1>
template <class Client, class Member>
Callback1Base<P1> *Callback1Base<P1>::make(Client &client_, Member member_)
{
    return new Callback1<P1, Client, Member>(client_, member_);
}

class CdPlayer
{
public:
    void playButtonPushed(Button *)
    {
        cout << "PLAY" << endl;
    }

    void stopButtonPushed(Button *)
    {
        cout << "STOP" << endl;
    }
};

class Button
{
public:
    Button()
    {
    }

    ~Button()
    {
    }

    template <class Client, class Member>
    void connect(const QString &signal, Client &client_, Member member_)
    {
        _connections[signal] << Callback1Base<Button*>::make(client_, member_);
    }

    void push()
    {
        foreach (Callback1Base<Button*> *_pCallback, _connections["push"]) {
            (*_pCallback)(this);
        }
    }

private:
    QHash<QString, QList<Callback1Base<Button*>*> > _connections;
};

int main(int, char **)
{
    CdPlayer cdPlayer;
    Button playButton;
    playButton.connect("push", cdPlayer, &CdPlayer::playButtonPushed);
    Button stopButton;
    stopButton.connect("push", cdPlayer, &CdPlayer::stopButtonPushed);
    playButton.push();
    stopButton.push();
    return 0;
}
