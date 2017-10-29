#include "PathFinding.h"

Engine::Core::PathFinding::PathFinding()
{
}

Engine::Core::PathFinding::~PathFinding()
{
}

void Engine::Core::PathFinding::CalculateEstimateDistance(Player Plr, Enemy E)
{
	Vector2f PlayerPosition = Plr.GetPosition();
	Vector2f EnemyPosition = E.GetPosition();

	this->EstimatedDistance = EuclideanDistance(PlayerPosition, EnemyPosition);
}
