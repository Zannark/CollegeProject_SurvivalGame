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
	Vector2i CurrentCell = this->Mesh->GetCellFromPosition(this->GetPosition());
	this->CurrentNode = this->Mesh->Get(CurrentCell);
	
	this->CurrentTotalMoves += 1;
	int MovementCost = this->CurrentTotalMoves + (int)this->CurrentNode.Estimate;

	///Four directions. Up, Down, Left, Right.
	///Check which has the smallest estimate.
	///The smallest estimate is the direction the enemy will go in.
	
	///This will get the estimates and store them for working out later on.
	vector<Vector2i> Estimates;

	///Up
	if(CurrentCell.y - 1 >= 0)
	{
		Estimates.push_back(Vector2i(CurrentCell.x, CurrentCell.y - 1));
	}

	///Down
	if (CurrentCell.y + 1 <= this->Mesh->GetHeight())
	{
		Estimates.push_back(Vector2i(CurrentCell.x, CurrentCell.y + 1));
	}

	///Left
	if (CurrentCell.x - 1 >= 0)
	{
		Estimates.push_back(Vector2i(CurrentCell.x - 1, CurrentCell.y));
	}

	///Right
	if (CurrentCell.x + 1 <= this->Mesh->GetHeight())
	{
		Estimates.push_back(Vector2i(CurrentCell.x + 1, CurrentCell.y));
	}
	
	vector<float> Heuristic = vector<float>(Estimates.size());

	for (int i = 0; i < Estimates.size(); i++)
	{
		auto Node = this->Mesh->Get(Estimates[i]);

		Heuristic[i] = Node.Estimate;
		Heuristic[i] = Node.Estimate;
	}

	int MinIndex = 0;
	float Min = Heuristic[MinIndex];

	for (int i = 1; i < Heuristic.size(); i++)
	{
		if (Heuristic[i] < Min && Heuristic[i] < Min)
		{
			Min = Heuristic[i];
			MinIndex = i;
		}
	}

	auto Position = Vector2f(Estimates[MinIndex].x, Estimates[MinIndex].y);
	this->Mesh->Get(Estimates[MinIndex]).Shape->setScale(Vector2f(3, 3));
	this->Texture->SetPosition(Vector2f(this->Mesh->GetCellFromPosition(Position)));
}
