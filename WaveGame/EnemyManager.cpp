#include "EnemyManager.h"

Engine::GamePlay::EnemyManager::EnemyManager(RenderWindow * Window, shared_ptr<Player> P)
{
	this->CurrentWave = 0;
	this->State = MatchState::NewMatch;
	this->P = P;
}

Engine::GamePlay::EnemyManager::~EnemyManager()
{
}

void Engine::GamePlay::EnemyManager::Update(RenderWindow* Window, Map M, float dt)
{
	if (this->State == MatchState::InMatch)
	{
		for (auto& En : this->Enemies)
		{
			if (En)
			{
				if(En->GetIsAlive())
					En->Update(Window, M, dt);
				else
					delete En;
			}
		}

		if (this->Enemies.size() == 0)
			this->State = MatchState::Interval;
	}
	else if (this->State == MatchState::Interval)
	{
		if (this->IntervalTimer >= INTERVAL_TIME)
		{
			this->State = MatchState::NewMatch;
			return;
		}

		this->IntervalTimer += dt;
	}
	else if (this->State == MatchState::NewMatch)
	{
		for (int i = 0; i < (DEFAULT_ENEMY_COUNT + CurrentWave); i++)
		{
			float x = rand() % Window->getSize().x;
			float y = rand() % Window->getSize().y;

			this->Enemies.push_back(new Enemy(Vector2f(x, y), Window, this->P));
		}

		this->State = MatchState::InMatch;
	}		
}

void Engine::GamePlay::EnemyManager::Draw(RenderWindow* Window)
{
	for (auto En : this->Enemies)
		En->Draw(Window);
}

/*vector<Enemy*> Engine::GamePlay::EnemyManager::GetEnemiesInRange(FloatRect BoundingBox)
{
	vector<Enemy*> ReturnValue;

	for (auto En : this->Enemies)
	{
		FloatRect Tester = FloatRect(En->GetPosition().x, En->GetPosition().y, En->GetSize().x, En->GetSize().y);

		if (Tester.intersects(BoundingBox))
			ReturnValue.push_back(En);
	}

	return ReturnValue;
}*/
