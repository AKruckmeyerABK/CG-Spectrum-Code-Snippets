#include "TrackingEnemy.h"
#include <windows.h>
#include <iostream>

TrackingEnemy::TrackingEnemy(int x, int y, Level* _levelPointer, Player* _playerPointer, unsigned int _stepsBeforeBreak, unsigned int _detectionRadius)
	: PlacableActor(x, y, ActorColor::Cyan), stepsBeforeBreak(_stepsBeforeBreak), detectionRaidus(_detectionRadius),
	levelPointer(_levelPointer), playerPointer(_playerPointer),
	stepCount(0), diagonalVertical(false), tracking(false)
{

}

void TrackingEnemy::Draw()
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_color);
	std::cout << (char)153;
	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}

void TrackingEnemy::Update()
{
	Point path;
	tracking = PlayerInRadius();

	if (tracking)
	{
		path = TrackingPath();
		UpdateDirection(path);
	}
}

bool TrackingEnemy::PlayerInRadius()
{
	int playerX = playerPointer->GetXPosition();
	int playerY = playerPointer->GetYPosition();

	int xDifference = playerX - GetXPosition();
	int yDifference = playerY - GetYPosition();

	float distance = sqrt(xDifference * xDifference + yDifference * yDifference);

	if(tracking)
		return detectionRaidus + 2 >= distance; // The enemy will lose the target once its 2 spaces out of the inital radius
	else
		return detectionRaidus >= distance;
}

Point TrackingEnemy::TrackingPath()
{
	int playerX = playerPointer->GetXPosition();
	int playerY = playerPointer->GetYPosition();

	int xDifference = playerX - GetXPosition();
	int yDifference = playerY - GetYPosition();

	//Velocity is 1 in the x and 1 in the y, before editing
	if (xDifference)
		xDifference = xDifference / abs(xDifference);
	if (yDifference)
		yDifference = yDifference / abs(yDifference);

	Point path = Point(xDifference, yDifference);
	
    //If the player is Diagonal, the enemy will zig zag to the player, maintaining a velocity of 1, alternating between an x and y axis move
	if (xDifference && yDifference)
	{
		//If theres no wall in the vetical path, move vertical, and then move horizontal next move
		if (diagonalVertical && !levelPointer->IsWall(GetXPosition(), GetYPosition() + path.y))
		{
			diagonalVertical = false;
			path.x = 0;
		}
		//else if there is no wall in the horizontal path, mover horizontal, and then move vertical, next move
		else if (!levelPointer->IsWall(GetXPosition() + path.x, GetYPosition()))
		{
			diagonalVertical = true;
			path.y = 0;
		}
		//This is a check if the enemy was slated to move horizontal, but had a wall blocking, so check if they can move vertical
		else if (!diagonalVertical && !levelPointer->IsWall(GetXPosition(), GetYPosition() + path.y))
		{
			diagonalVertical = false;
			path.x = 0;
		}
		//Enemy is stuck in a corner; do not move
		else
		{
			path = Point(0, 0);
		}
	}
	else//checking for walls normally
	{
		if (path.x && levelPointer->IsWall(GetXPosition() + path.x, GetYPosition()))
			path.x = 0;
		else if (levelPointer->IsWall(GetXPosition(), GetYPosition() + path.y))
			path.y = 0;
	}
	return path;
}

void TrackingEnemy::UpdateDirection(Point path)
{
	//If the enemy makes a certain amount of uninterupted steps, then take a one turn break
	//Becoming stuck on a corner counts as taking a break
	if (stepCount >= stepsBeforeBreak  || (path.x == 0 && path.y == 0))
	{
		stepCount = 0;
		return;
	}

	SetPosition(m_pPosition->x + path.x, m_pPosition->y + path.y);
	stepCount++;
}