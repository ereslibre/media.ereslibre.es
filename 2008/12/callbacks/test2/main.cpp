#include <QList>
#include <QString>
#include <QHash>

#include <iostream>

using namespace std;
class Button;

// dummy base class
class CallbackBase
{
};

template <class P1>
class Callback1Base
    : public CallbackBase
{
public:
    virtual void operator()(P1) const = 0;
    virtual Callback1Base<P1> *clone() const = 0;

    template <class Client, class Member>
    static Callback1Base<P1> *make(Client &client_, Member member_);
};

template <class P1, class P2>
class Callback2Base
    : public CallbackBase
{
public:
    virtual void operator()(P1, P2) const = 0;
    virtual Callback2Base<P1, P2> *clone() const = 0;

    template <class Client, class Member>
    static Callback2Base<P1, P2> *make(Client &client_, Member member_);
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

template <class P1, class P2, class Client, class Member>
class Callback2
    : public Callback2Base<P1, P2>
{
public:
    Callback2(Client &client_, Member member_)
        : _client(client_)
        , _member(member_)
    {
    }

    virtual void operator()(P1 parm_, P2 parm2_) const
    {
        ((&_client)->*_member)(parm_, parm2_);
    }

    virtual Callback2<P1, P2, Client, Member> *clone() const
    {
        return new Callback2<P1, P2, Client, Member>(*this);
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

template <class P1, class P2>
template <class Client, class Member>
Callback2Base<P1, P2> *Callback2Base<P1, P2>::make(Client &client_, Member member_)
{
    return new Callback2<P1, P2, Client, Member>(client_, member_);
}

class CdPlayer
{
public:
    void playButtonPushed(Button *, bool whatThe)
    {
        cout << "PLAY (got as parameter: " << whatThe << ")" << endl;
    }

    void stopButtonPushed(Button *, bool whatThe)
    {
        cout << "STOP (got as parameter: " << whatThe << ")" << endl;
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
        _connections[signal] << Callback2Base<Button*, bool>::make(client_, member_);
    }

    void push(bool whatThe)
    {
        QList<CallbackBase*> list = _connections[__func__];
        for (int i = 0; i < list.count(); ++i) {
            (*static_cast<Callback2Base<Button*, bool>*>(list[i]))(this, whatThe);
        }
    }

private:
    QHash<QString, QList<CallbackBase*> > _connections;
};

int main(int, char **)
{
    CdPlayer cdPlayer;
    Button playButton;
    playButton.connect("push", cdPlayer, &CdPlayer::playButtonPushed);
    Button stopButton;
    stopButton.connect("push", cdPlayer, &CdPlayer::stopButtonPushed);
    playButton.push(false);
    stopButton.push(true);
    return 0;
}
