#include <iostream>

using namespace std;
class Button;

class CdPlayer
{
public:
    void buttonPushed(Button *pButton_)
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
    Button(CdPlayer *pCdPlayer_)
	: _pCdPlayer(pCdPlayer_)
    {
    }

    void push()
    {
	_pCdPlayer->buttonPushed(this);
    }

private:
    CdPlayer *_pCdPlayer;
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
