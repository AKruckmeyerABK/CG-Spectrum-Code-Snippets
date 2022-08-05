#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <windows.h>
#include <vector>
#include <string>
#include <thread>
#include <mutex>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	StateMachineExampleGame* m_pOwner;
	
	Player m_player;
	Level* m_pLevel;

	bool m_beatLevel;
	int m_skipFrameCount;
	static constexpr int kFramesToSkip = 2;

	int m_currentLevel;

	std::vector<std::string> m_LevelNames;

	std::thread GameplayThread;
	std::thread DrawThread;
	bool endThreads = false;

	std::mutex PlayerActorStepMutex;

public:
	GameplayState(StateMachineExampleGame* pOwner);
	~GameplayState();

	virtual bool ProcessInput() override;
	virtual void Enter() override;
	virtual void Exit() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;

private:
	void CheckBeatLevel();
	void HandleCollision(int newPlayerX, int newPlayerY);
	void ActorUpdate_Threaded();
	void Draw_Threaded();
	bool Load();
	void DrawHUD(const HANDLE& console);
};
