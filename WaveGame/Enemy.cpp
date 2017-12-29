#include "Enemy.h"

Engine::GamePlay::Enemy::Enemy(Vector2f Position, RenderWindow* Window, shared_ptr<Player> P)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Enemy.png"));
	this->Texture->SetPosition(Position);
	this->Window = Window;
	this->P = P;
	this->State = EnemyState::CheckDistance;
	this->SearchState = 0;
	this->MovementPercentage = 0;
	this->StartNode = NavigationNode(Position, Window, false);
	this->EndNode = NavigationNode(this->AlignPlayer(), Window, false);
	this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
	this->HasStarted = false;
	this->FinishedPath = false;
	this->Health = 15;
	this->AttackDamage = 3;
	this->AttackTimer = ENEMY_ATTACK_INTERVAL;
	this->MovementSpeed = ((float)rand() / (float)RAND_MAX) * ENEMY_MAX_MOVEMENT_SPEED + ENEMY_MIN_MOVEMENT_SPEED;

	this->IsAlive = true;
}

Engine::GamePlay::Enemy::~Enemy()
{
}

void Engine::GamePlay::Enemy::Update(RenderWindow* Window, Map M, float dt)
{
	this->ManageState();
}

bool Engine::GamePlay::Enemy::GetIsAlive(void)
{
	return this->IsAlive;
}

void Engine::GamePlay::Enemy::ManageState(void)
{
	if (this->State == EnemyState::Pathfinding)
		this->FindPath();
	else if (this->State == EnemyState::CheckDistance)
		this->CheckDistance();
	else if (this->State == EnemyState::Attacking)
		this->Attack();
}

void Engine::GamePlay::Enemy::FindPath(void)
{
	do 
	{
		this->SearchState = this->Search.SearchStep();
	} while (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_SEARCHING);
			
	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_NOT_INITIALISED)
	{
		cout << "Not Initalised" << endl;
		this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
	}

	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_FAILED)
	{
		cout << "Failed" << endl;
	}

	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_SUCCEEDED)
	{
		if (!HasStarted)
		{
			this->CurrentNode = this->Search.GetSolutionStart();
			this->HasStarted = true;
		}
		else
		{
			if (this->MovementPercentage >= 1)
			{
				if (this->EndNode.Position != this->AlignPlayer())
				{
					this->Search.FreeSolutionNodes();
					this->EndNode = NavigationNode(this->AlignPlayer(), Window, false);
					this->StartNode = NavigationNode(this->GetPosition(), Window, false);

					this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
					this->SearchState = AStarSearch<NavigationNode>::SEARCH_STATE_SEARCHING;
					this->HasStarted = false;
					return;
				}

				this->NodePosition = this->GetPosition();
				this->CurrentNode = this->Search.GetSolutionNext();
				this->MovementPercentage = 0;
			}
			
			if (!this->CurrentNode)
			{
				this->State = EnemyState::CheckDistance;
				this->HasStarted = false;
				return;
			}
	
			if (this->MovementPercentage < 1)
			{
				this->CheckDistance();

				if (this->State != Pathfinding)
					this->Attack();

				this->MovementPercentage += this->MovementSpeed * GameTime::DeltaTime();
				Vector2f Pos = Lerp(this->NodePosition, this->CurrentNode->Position, this->MovementPercentage);
				
				if (Pos.x < this->GetPosition().x)
					Pos.x += Div(Abs(Pos - this->GetPosition()), 2).x;

				if (Pos.y < this->GetPosition().y)
					Pos.y += Div(Abs(Pos - this->GetPosition()), 2).y;

				this->SetPosition(Pos);
			}
		}
	}
}

void Engine::GamePlay::Enemy::CheckDistance(void)
{
	if (Distance(this->GetPosition(), this->P->GetPosition()).x <= ENEMY_ATTACK_RANGE && Distance(this->GetPosition(), this->P->GetPosition()).y <= ENEMY_ATTACK_RANGE)
		this->State = EnemyState::Attacking;
	else
		this->State = EnemyState::Pathfinding;
}

void Engine::GamePlay::Enemy::Attack(void)
{
	if (this->AttackTimer >= ENEMY_ATTACK_INTERVAL)
	{
		this->P->TakeDamage(rand() % this->AttackDamage);
		this->AttackTimer = 0;
	}
	else
		this->AttackTimer += GameTime::DeltaTime();

	this->State = EnemyState::CheckDistance;
}

Vector2f Engine::GamePlay::Enemy::AlignPlayer(void)
{
	int AlignedX = (int)(P->GetPosition().x / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
	int AlignedY = (int)(P->GetPosition().y / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;

	return Vector2f((float)AlignedX, (float)AlignedY);
}

