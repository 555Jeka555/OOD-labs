#include "iostream"

class IAudioPlayerButton
{
public:
    virtual void Print() = 0;
    virtual void Click() = 0;

    virtual void SetPlayState() = 0;
    virtual void SetPauseState() = 0;

    ~IAudioPlayerButton() = default;
};

class IState
{
public:
    virtual void Display() = 0;

    virtual void Click() = 0;

    ~IState() = default;
};

class PauseState : public IState
{
public:
    PauseState(IAudioPlayerButton & audioPlayer) : m_audioPlayer(audioPlayer) {}

    void Display()
    {
        std::cout << "Audio play stopped" << std::endl;
    }

    void Click()
    {
        m_audioPlayer.SetPlayState();
    }
private:
    IAudioPlayerButton & m_audioPlayer;
};

class PlayState : public IState
{
public:
    PlayState(IAudioPlayerButton & audioPlayer) : m_audioPlayer(audioPlayer) {}

    void Display()
    {
        std::cout << "Audio play is activw" << std::endl;
    }

    void Click()
    {
        m_audioPlayer.SetPauseState();
    }
private:
    IAudioPlayerButton & m_audioPlayer;
};

class AudioPlayerButton : private IAudioPlayerButton
{
public:
    void Print() override
    {
        m_state->Display();
    }

    void Click() override
    {
        m_state->Click();
    }

private:
    IState * m_state;

};


int main()
{
    return 0;
}