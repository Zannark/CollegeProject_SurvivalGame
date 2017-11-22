#include "Enemy.h"



Engine::GamePlay::Enemy::Enemy(shared_ptr<NavigationMesh> Mesh, Vector2f Position)
{
	this->Mesh = Mesh;
	this->CurrentTotalMoves = 0;

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
	this->CurrentNode = this->Mesh->Get(this->Mesh->GetCellFromPosition(this->GetPosition()));
	
	this->CurrentTotalMoves += 1;
	int MovementCost = this->CurrentTotalMoves + (int)this->CurrentNode.Estimate;

	cout << "MovementCost = " << MovementCost << endl;
}
