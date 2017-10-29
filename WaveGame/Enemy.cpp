#include "Enemy.h"



Engine::GamePlay::Enemy::Enemy(shared_ptr<NavigationMesh> Mesh)
{
	this->Mesh = Mesh;
}

Engine::GamePlay::Enemy::~Enemy()
{
}

void Engine::GamePlay::Enemy::Update(shared_ptr<RenderWindow> Window, Map M, float dt)
{
}
