#include <iostream>

using namespace std;
class Button;

template <class P1>
class Callback1Base
{
public:
    virtual void operator()(P1) const = 0;
    virtual Callback1Base<P1> *clone() const = 0;
};

template <class P1, class Client>
class Callback1
    : public Callback1Base<P1>
{
public:
    typedef void (Client::*PMEMFUNC)(P1);
    Callback1(Client &client_, PMEMFUNC pMemfunc_)
	: _client(client_)
	, _pMemfunc(pMemfunc_)
    {
    }

    virtual void operator()(P1 parm_) const
    {
	(_client.*_pMemfunc)(parm_);
    }

    virtual Callback1<P1, Client> *clone() const
    {
	return new Callback1<P1, Client>(*this);
    }

private:
    Client &_client;
    PMEMFUNC _pMemfunc;
};

class Button
{
public:
    Button(Callback1Base<Button*> const &callback_)
	: _pCallback(callback_.clone())
    {
    }

    ~Button()
    {
	delete _pCallback;
    }

    void push()
    {
	(*_pCallback)(this);
    }

private:
    Callback1Base<Button*> *_pCallback;
};

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

int main(int, char **)
{
    CdPlayer cdPlayer;
    Callback1<Button*, CdPlayer> playCallback(cdPlayer, &CdPlayer::playButtonPushed);
    Callback1<Button*, CdPlayer> stopCallback(cdPlayer, &CdPlayer::stopButtonPushed);
    Button playButton(playCallback);
    Button stopButton(stopCallback);
    playButton.push();
    stopButton.push();
    return 0;
}
