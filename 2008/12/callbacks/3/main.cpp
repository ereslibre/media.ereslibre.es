#include <iostream>

using namespace std;
class Button;

class ButtonClient
{
public:
    virtual void buttonPushed(Button *) = 0;
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

class CdPlayerAdaptor
    : public ButtonClient
{
public:
    CdPlayerAdaptor(CdPlayer *pCdPlayer_)
	: _pCdPlayer(pCdPlayer_)
    {
    }

    virtual void buttonPushed(Button *pButton_)
    {
	if (pButton_ == _pPlayButton) _pCdPlayer->playButtonPushed(pButton_);
	else if (pButton_ == _pStopButton) _pCdPlayer->stopButtonPushed(pButton_);
    }

    void setPlayButton(Button *pButton_)
    {
	_pPlayButton = pButton_;
    }

    void setStopButton(Button *pButton_)
    {
	_pStopButton = pButton_;
    }

private:
    Button *_pPlayButton;
    Button *_pStopButton;
    CdPlayer *_pCdPlayer;
};

class Button
{
public:
    Button(ButtonClient *pClient_)
	: _pClient(pClient_)
    {
    }

    void push()
    {
	_pClient->buttonPushed(this);
    }

private:
    ButtonClient *_pClient;
};


int main(int, char **)
{
    CdPlayer cdPlayer;
    CdPlayerAdaptor cdPlayerAdaptor(&cdPlayer);
    Button playButton(&cdPlayerAdaptor);
    Button stopButton(&cdPlayerAdaptor);
    cdPlayerAdaptor.setPlayButton(&playButton);
    cdPlayerAdaptor.setStopButton(&stopButton);
    playButton.push();
    stopButton.push();
    return 0;
}
