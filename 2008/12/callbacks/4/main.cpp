#include <iostream>

using namespace std;
class Button;

class ButtonClient
{
public:
    virtual void buttonPushed(Button *) = 0;
};

template <class T>
class ExternalPolymorph
    : public ButtonClient
{
public:
    ExternalPolymorph(T *pT_)
	: _pT(pT_)
    {
    }

    virtual void buttonPushed(Button *pButton_)
    {
	_pT->myButtonPushed(pButton_);
    }

private:
    T *_pT;
};

class CdPlayer
{
public:
    void myButtonPushed(Button *pButton_)
    {
	if (pButton_ == _pPlayButton) playButtonPushed(pButton_);
	else if (pButton_ == _pStopButton) stopButtonPushed(pButton_);
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
    ExternalPolymorph<CdPlayer> externalPolymorph(&cdPlayer);
    Button playButton(&externalPolymorph);
    Button stopButton(&externalPolymorph);
    cdPlayer.setPlayButton(&playButton);
    cdPlayer.setStopButton(&stopButton);
    playButton.push();
    stopButton.push();
    return 0;
}
