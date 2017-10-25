#include "Enemy.h"



Engine::GamePlay::Enemy::Enemy(shared_ptr<NavigationMesh> Mesh)
{
	this->Mesh = Mesh;
}

Engine::GamePlay::Enemy::~Enemy()
{
}
