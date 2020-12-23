//State Pattern
//Consider a MusicPlayer
//Has 3 states: Playing, Paused and Stopped
//Has 3 actions: Play, Pause, Stop

#include<iostream>
#include<string>
using namespace std;

//forward declaration
class MusicPlayer;

//MusicPlayerState Interface
class MusicPlayerState {
public:
	MusicPlayerState(std::string name);
	virtual ~MusicPlayerState();
    //note that these are not pure virtual functions
	//this is because we define some default illegal state transition behaviours
	//through these action methods
	//note that this depends on the state relationships
	//if there is no illegal or default behaviour
	//these action methods can be declared as pure virtual methods
	virtual void Play(MusicPlayer * player);
	virtual void Pause(MusicPlayer * player);
	virtual void Stop(MusicPlayer * player);

	std::string GetName() { return m_name; }

private:
	std::string   m_name;
};

//MusicPlayer class
//Holds Current State of the MusicPlayer
class MusicPlayer {
public:
	enum State
	{
		ST_STOPPED,
		ST_PLAYING,
		ST_PAUSED
	};

	MusicPlayer();
	virtual ~MusicPlayer();
    //actions on MusicPlayer
	void Play();
	void Pause();
	void Stop();
    //changes state of MusicPlayer depending on action taken
	void SetState(State state);

private:
	MusicPlayerState * m_pState;
};

//Note that the MusicPlayer method are defined way later to avoid class dependency problems

MusicPlayerState::MusicPlayerState(std::string name)
: m_name(name) {
}

MusicPlayerState::~MusicPlayerState() {
}

void MusicPlayerState::Play(MusicPlayer *)
{
	std::cout << "Illegal state transition from " << GetName() << " to Playing\n";
}

void MusicPlayerState::Pause(MusicPlayer *)
{
	std::cout << "Illegal state transition from " << GetName() << " to Paused\n";
}

void MusicPlayerState::Stop(MusicPlayer *)
{
	std::cout << "Illegal state transition from " << GetName() << " to Stopped\n";
}

//Concrete class PlayingState implements MusicPlayerState Interface
class PlayingState : public MusicPlayerState {
public:
	PlayingState();
	virtual ~PlayingState();
    //note that only actions that enable legal state transition are defined below
	//state transition from PlayingState to PlayingState is not allowed on action 'play'
	//so the action 'play' is not defined here
	//if the action 'play' is taken on this State,
	//the play() method in MusicPlayerState interface is called
	virtual void Pause(MusicPlayer * player);
	virtual void Stop(MusicPlayer * player);
};

PlayingState::PlayingState()
: MusicPlayerState(std::string("Playing")) {
}

PlayingState::~PlayingState() {
}

void PlayingState::Pause(MusicPlayer * player)
{
	player->SetState(MusicPlayer::ST_PAUSED);
}

void PlayingState::Stop(MusicPlayer * player)
{
	player->SetState(MusicPlayer::ST_STOPPED);
}

class PausedState : public MusicPlayerState {
public:
	PausedState();
	virtual ~PausedState();

	virtual void Play(MusicPlayer * player);
	virtual void Stop(MusicPlayer * player);
};

PausedState::PausedState()
: MusicPlayerState(std::string("Paused")) {
}

PausedState::~PausedState() {
}

void PausedState::Play(MusicPlayer * player)
{
	player->SetState(MusicPlayer::ST_PLAYING);
}

void PausedState::Stop(MusicPlayer * player)
{
	player->SetState(MusicPlayer::ST_STOPPED);
}

class StoppedState : public MusicPlayerState {
public:
	StoppedState();
	virtual ~StoppedState();

	virtual void Play(MusicPlayer * player);
};

StoppedState::StoppedState()
: MusicPlayerState(std::string("Stopped")) {
}

StoppedState::~StoppedState() {
}

void StoppedState::Play(MusicPlayer * player)
{
	player->SetState(MusicPlayer::ST_PLAYING);
}

//MusciPlayer Constructor initializes object with Stopped State
MusicPlayer::MusicPlayer()
: m_pState(new StoppedState()){

}

MusicPlayer::~MusicPlayer() {
	delete m_pState;
}

void MusicPlayer::Play() {
	m_pState->Play(this);
}

void MusicPlayer::Pause() {
	m_pState->Pause(this);
}

void MusicPlayer::Stop() {
	m_pState->Stop(this);
}

void MusicPlayer::SetState(State state)
{
	std::cout << "changing from " << m_pState->GetName() << " to ";
	delete m_pState;

	if(state == ST_STOPPED)
	{
		m_pState = new StoppedState();
	}
	else if(state == ST_PLAYING)
	{
		m_pState = new PlayingState();
	}
	else
	{
		m_pState = new PausedState();
	}

	std::cout << m_pState->GetName() << " state\n";
}



int main()
{
	MusicPlayer player;

	player.Play();
	player.Play();
	player.Pause();
	player.Stop();


	return 0;
}
