#include "Enemy.h"



Engine::GamePlay::Enemy::Enemy(shared_ptr<NavigationMesh> Mesh)
{
	this->Mesh = Mesh;
	this->CurrentTotalMoves = 0;
}

Engine::GamePlay::Enemy::~Enemy()
{
}

void Engine::GamePlay::Enemy::Update(shared_ptr<RenderWindow> Window, Map M, float dt)
{
}

void Engine::GamePlay::Enemy::CalculateNextNode()
{
	//this->CurrentNode = this->Mesh->Get(this->CurrentTotalMoves);
	this->CurrentTotalMoves += 1;
	
	int MovementCost = this->CurrentTotalMoves + (int)this->CurrentNode.Estimate;

	///https://www.redblobgames.com/pathfinding/a-star/introduction.html
}
