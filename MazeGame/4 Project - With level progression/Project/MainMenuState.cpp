#include "MainMenuState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScore = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

bool MainMenuState::ProcessInput()
{
	int input = _getch();

	if (input == kEscapeKey || (char)input == kQuit)
	{
		return true;
	}
	else if ((char)input == kPlay)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
	}
	else if ((char)input == kHighScore)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::HighScore);
	}
	else if ((char)input == kSettings)
	{
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
	}

	return false;
}

bool MainMenuState::Update(bool processInput)
{
	if (processInput)
	{
		return ProcessInput();
	}
	return false;
}

void MainMenuState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "          - - - MAIN MENU - - -" << endl << endl;
	cout << "             " << kPlay << ". Play " << endl;
	cout << "             " << kHighScore << ". High Score " << endl;
	cout << "             " << kSettings << ". Settings " << endl;
	cout << "             " << kQuit << ". Quit " << endl;
}