#include "Enemy.h"

Engine::GamePlay::Enemy::Enemy(Vector2f Position)
{

	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Enemy.png"));
	this->Texture->SetPosition(Position);

}

Engine::GamePlay::Enemy::~Enemy()
{
}

void Engine::GamePlay::Enemy::Update(shared_ptr<RenderWindow> Window, Map M, float dt)
{
	this->CalculateNextNode();
}

void Engine::GamePlay::Enemy::CalculateNextNode()
{
	
}
