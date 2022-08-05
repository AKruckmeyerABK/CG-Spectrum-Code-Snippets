#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class SettingsState : public GameState
{
	StateMachineExampleGame* m_pOwner;

public:
	SettingsState(StateMachineExampleGame* pOwner);
	~SettingsState() = default;

	virtual bool ProcessInput() override;
	virtual bool Update(bool processInput = true) override;
	virtual void Draw() override;
};
