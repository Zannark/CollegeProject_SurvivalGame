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
	
	auto EstimateWithHeuristic = Estimates;

	for (int i = 0; i < Estimates.size(); i++)
	{
		auto Node = this->Mesh->Get(Estimates[i]);

		EstimateWithHeuristic[i].x += Node.Estimate;
		EstimateWithHeuristic[i].y += Node.Estimate;
	}

	///Vector2i DirectionToGo = *min_element(Estimates.begin(), Estimates.end(), VectorLessThan);

	int MaxIndex = 0;
	auto Max = EstimateWithHeuristic[MaxIndex];

	for (int i = 1; i < EstimateWithHeuristic.size(); i++)
	{
		if (EstimateWithHeuristic[i].x > Max.x && EstimateWithHeuristic[i].y > Max.y)
		{
			Max = EstimateWithHeuristic[i];
			MaxIndex = i;
		}
	}

	cout << this->Mesh->Get(Estimates[MaxIndex]).Point.x << " " << this->Mesh->Get(Estimates[MaxIndex]).Point.y << endl;
	this->Texture->SetPosition(Vector2f(this->Mesh->GetCellFromPosition(this->Mesh->Get(Estimates[MaxIndex]).Point)));
}
