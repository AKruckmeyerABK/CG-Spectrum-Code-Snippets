#pragma once
#include "PlacableActor.h"
#include "Player.h"
#include "Level.h"

//Tracking enemy is represented by t in the level editor
//Tracking enemy will follow the player at araidus, and will zigzag when moving diagonally
//Tracking enemy will take a break moving every 3 steps
//Will not move through walls
class TrackingEnemy : public PlacableActor
{
public:
	TrackingEnemy(int x, int y, Level* _levelPointer, Player *_playerPointer, unsigned int _stepsBeforeBreak = 3, unsigned int _detectionRadius = 5);

	virtual ActorType GetType() override { return ActorType::TrackingEnemy; }
	virtual void Draw() override;
	virtual void Update() override;

private:
	unsigned int detectionRaidus;
	unsigned int stepsBeforeBreak;

	unsigned int stepCount;
	bool diagonalVertical;
	bool tracking;

	Player* playerPointer;
	Level* levelPointer;

	bool PlayerInRadius();
	Point TrackingPath();
	void UpdateDirection(Point path);

};