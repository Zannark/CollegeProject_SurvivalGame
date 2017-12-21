#include "Enemy.h"

Engine::GamePlay::Enemy::Enemy(Vector2f Position, shared_ptr<RenderWindow> Window, shared_ptr<Player> P)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Enemy.png"));
	this->Texture->SetPosition(Position);
	this->Window = Window;
	this->P = P;
	this->State = EnemyState::Pathfinding;
	this->SearchState = 0;
	this->StartNode = NavigationNode(Position, Window, false);

	int AlignedX = (int)(P->GetPosition().x / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
	int AlignedY = (int)(P->GetPosition().y / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;

	this->EndNode = NavigationNode(Vector2f(AlignedX, AlignedY), Window, false);
	this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
	this->HasStarted = false;
	this->FinishedPath = false;
}

Engine::GamePlay::Enemy::~Enemy()
{
}

void Engine::GamePlay::Enemy::Update(shared_ptr<RenderWindow> Window, Map M, float dt)
{
	this->ManageState();
}

void Engine::GamePlay::Enemy::ManageState(void)
{
	if (this->State == EnemyState::Pathfinding)
		this->FindPath();
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
		this->Search.FreeSolutionNodes();
		int AlignedX = (int)(P->GetPosition().x / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
		int AlignedY = (int)(P->GetPosition().y / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
		this->EndNode = NavigationNode(Vector2f(AlignedX, AlignedY), Window, false);
		this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);
		cout << "Failed" << endl;
	}

	if (this->SearchState == AStarSearch<NavigationNode>::SEARCH_STATE_SUCCEEDED)
	{
		if (!HasStarted)
		{
			this->CurrentNode = this->Search.GetSolutionStart();
			this->HasStarted = true;
			
			this->SetPosition(this->CurrentNode->Position);		
		}
		else
		{
			this->CurrentNode = this->Search.GetSolutionNext();
			
			if (!this->CurrentNode)
			{
				this->Search.FreeSolutionNodes();
				int AlignedX = (int)(P->GetPosition().x / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
				int AlignedY = (int)(P->GetPosition().y / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
				this->EndNode = NavigationNode(Vector2f(AlignedX, AlignedY), Window, false);
				this->Search.SetStartAndGoalStates(this->StartNode, this->EndNode);

				//this->State = EnemyState::CheckDistance;
				this->HasStarted = false;
				return;
			}
	
			this->SetPosition(this->CurrentNode->Position);
		}
	}
}

