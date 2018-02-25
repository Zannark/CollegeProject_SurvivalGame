#include "Enemy.h"

///BUG: TODO: FPS drop - investigate could just be FFXIV running in the background but shouldn't cause that bad stuttering...

Engine::GamePlay::Enemy::Enemy(Vector2f Position, RenderWindow* Window, Player* P, float Speed)
{
	this->CharacterAnimator = make_shared<Animator>(AnimationCache::Cache("Assets/Enemy.png"));
	this->CharacterAnimator->SetPosition(Position);
	this->Window = Window;
	this->P = P;
	this->State = EnemyState::CheckDistance;
	this->SearchState = 0;
	this->MovementPercentage = 0;
	this->StartNode = NavigationNode(Position, Window, false);
	this->EndNode = NavigationNode(AlignPlayer((void*)P), Window, false);
	this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
	this->HasStarted = false;
	this->FinishedPath = false;
	this->Health = ENEMY_MAX_HEALTH;
	this->AttackTimer = ENEMY_ATTACK_INTERVAL;
	this->IsAlive = true;
	this->MovementSpeed = Speed;
}

Engine::GamePlay::Enemy::~Enemy()
{
}

///<summary>
///Called once per frame, updates the enemy.
///</summary>
///<param name = "Window">A pointer to the RenderWindow which is being used.</param>
///<param name = "M">A copy of the Map for the player for movement.</param>
///<param name = "dt">Delta time, the time the last frame took.</param>
void Engine::GamePlay::Enemy::Update(RenderWindow* Window, Map M, float dt)
{
	this->ManageState();
	this->AttackTimer += GameTime::DeltaTime();
}

///<summary>
///Carries out different functions, depending on the current state.
///</summary>
void Engine::GamePlay::Enemy::ManageState(void)
{
	if (this->State == EnemyState::Pathfinding)
		this->FindPath();
	else if (this->State == EnemyState::CheckDistance)
		this->CheckDistance();
	else if (this->State == EnemyState::Attacking)
		this->Attack();
}

///<summary>
///Carries out A* pathfinding, moving towards the player.
///</summary>
void Engine::GamePlay::Enemy::FindPath(void)
{
	do 
	{
		this->SearchState = this->Search.SearchStep();
	} while (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_SEARCHING);
			
	cout << this->SearchState << endl;

	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_NOT_INITIALISED)
	{
		cout << "Not Initalised" << endl;
		this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
	}

	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_FAILED)
	{
		this->Health = 0;
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
				if (this->EndNode.Position != AlignPlayer((void*)P))
				{
					this->Search.FreeSolutionNodes();
					this->EndNode = NavigationNode(AlignPlayer((void*)P), Window, false);
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

///<summary>
///Checks how far away the player is from the ememy.
///</summary>
void Engine::GamePlay::Enemy::CheckDistance(void)
{
	if (Distance(this->GetPosition(), this->P->GetPosition()).x <= ENEMY_ATTACK_RANGE && Distance(this->GetPosition(), this->P->GetPosition()).y <= ENEMY_ATTACK_RANGE)
		this->State = EnemyState::Attacking;
	else
		this->State = EnemyState::Pathfinding;
}

///<summary>
///Attacks the player, random amount between 0 and ENEMY_ATTACK_INTERVAL.
///</summary>
void Engine::GamePlay::Enemy::Attack(void)
{
	if (this->AttackTimer >= ENEMY_ATTACK_INTERVAL)
	{
		this->P->TakeDamage(ENEMY_MIN_ATTACK + rand() % (ENEMY_MAX_ATTACK - ENEMY_MIN_ATTACK));
		this->AttackTimer = 0;
	}

	this->State = EnemyState::CheckDistance;
}

