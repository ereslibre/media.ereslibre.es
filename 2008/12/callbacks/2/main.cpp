#include <iostream>

using namespace std;
class Button;

class ButtonClient
{
public:
    virtual void buttonPushed(Button *) = 0;
};

class CdPlayer
    : public ButtonClient
{
public:
    virtual void buttonPushed(Button *pButton_)
    {
	if (pButton_ == _pPlayButton) this->playButtonPushed(pButton_);
	else if (pButton_ == _pStopButton) this->stopButtonPushed(pButton_);
    }

    void setPlayButton(Button *pButton_)
    {
	_pPlayButton = pButton_;
    }

    void setStopButton(Button *pButton_)
    {
	_pStopButton = pButton_;
    }

    void playButtonPushed(Button *)
    {
	cout << "PLAY" << endl;
    }

    void stopButtonPushed(Button *)
    {
	cout << "STOP" << endl;
    }

private:
    Button *_pPlayButton;
    Button *_pStopButton;
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
    Button playButton(&cdPlayer);
    Button stopButton(&cdPlayer);
    cdPlayer.setPlayButton(&playButton);
    cdPlayer.setStopButton(&stopButton);
    playButton.push();
    stopButton.push();
    return 0;
}
