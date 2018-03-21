#include "Enemy.h"

///<summary>
///Constructs the enemy object.
///Loads the Animator from the cache.
///</summary>
///<param name = "Position">The position to set the enemy at.</param>
///<param name = "Window">The window which is being rendered to.</param>
///<param name = "P">The player which is being currently used.</param>
///<param name = "Speed">The speed (in pixels per second) the enemy can move at.</param>
Engine::GamePlay::Enemy::Enemy(Vector2f Position, RenderWindow* Window, Player* P, float Speed)
{
	this->CharacterAnimator = make_shared<Animator>(Animator(AnimationCache::Cache("Assets/Enemy.png")));
	this->CharacterAnimator->SetPosition(Position);
	this->CharacterAnimator->SetOrigin(Div(this->CharacterAnimator->GetSize(), 2));
	this->Window = Window;
	this->P = P;
	this->State = EnemyState::CheckDistance;
	this->SearchState = 0;
	this->MovementPercentage = 0;
	this->StartNode = NavigationNode(Position, Window, false);
	this->EndNode = NavigationNode(AlignPlayer((void*)P), Window, false);
	this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
	this->HasStarted = false;
	this->Health = ENEMY_MAX_HEALTH;
	this->AttackTimer = ENEMY_ATTACK_INTERVAL;
	this->IsAlive = true;
	this->MovementSpeed = Speed;
	this->RecieveDamageColour = Color(255, 0, 0);
	this->DefaultColour = this->CharacterAnimator->GetSFMLSprite()->getColor();
	this->ColourChangeTimer = 0.0f;
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

	if (this->CharacterAnimator->GetSFMLSprite()->getColor() != this->DefaultColour && this->ColourChangeTimer >= ENEMY_RECIEVE_DAMAGE_COLOUR_CHANGE_LENGTH)
		this->CharacterAnimator->GetSFMLSprite()->setColor(this->DefaultColour);
	else
		this->ColourChangeTimer += dt;
}

void Engine::GamePlay::Enemy::TakeDamage(int Amount)
{
	Character::TakeDamage(Amount);
	this->CharacterAnimator->GetSFMLSprite()->setColor(this->RecieveDamageColour);
	this->ColourChangeTimer = 0.0f;
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

	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_NOT_INITIALISED)
	{
		cout << "Not Initalised" << endl;
		this->Search.FreeSolutionNodes();
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
					this->EndNode = NavigationNode(AlignPlayer((void*)P), this->Window, false);
					this->StartNode = NavigationNode(this->GetPosition(), this->Window, false);

					this->Search.FreeSolutionNodes();
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
	const Vector2f PlayerDistance = Distance(this->GetPosition(), this->P->GetPosition());

	if (PlayerDistance.x <= ENEMY_ATTACK_RANGE && PlayerDistance.y <= ENEMY_ATTACK_RANGE)
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

