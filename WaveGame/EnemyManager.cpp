#include "EnemyManager.h"

Engine::GamePlay::EnemyManager::EnemyManager(RenderWindow * Window, shared_ptr<Player> P)
{
	this->CurrentWave = 0;
	this->State = MatchState::NewMatch;
	this->P = P;
	this->IntervalTimer = 0.f;
}

Engine::GamePlay::EnemyManager::~EnemyManager()
{
}

void Engine::GamePlay::EnemyManager::Update(RenderWindow* Window, Map M, float dt)
{
	if (this->State == MatchState::InMatch)
	{
		bool NewMatch = true;

		for (auto& En : this->Enemies)
		{
			if (En->CheckHealth())
			{
				En->Update(Window, M, dt);
				NewMatch = false;
			}
		}

		if (NewMatch)
			this->State = MatchState::Interval;
	}
	else if (this->State == MatchState::Interval)
	{
		if (this->IntervalTimer >= INTERVAL_TIME)
		{
			for (int i = 0; i < Enemies.size(); i++)
				delete Enemies[i];

			this->CurrentWave += 1;
			this->IntervalTimer = 0;
			this->State = MatchState::NewMatch;
			return;
		}

		this->IntervalTimer += dt;
		cout << IntervalTimer << endl;
	}
	else if (this->State == MatchState::NewMatch)
	{
		this->Enemies = vector<Enemy*>();

		for (int i = 0; i < (DEFAULT_ENEMY_COUNT + CurrentWave); i++)
		{
			float x = (float)(rand() % Window->getSize().x);
			float y = (float)(rand() % Window->getSize().y);

			this->Enemies.push_back(new Enemy(Vector2f(x, y), Window, this->P));
		}

		this->State = MatchState::InMatch;
	}		
}

void Engine::GamePlay::EnemyManager::Draw(RenderWindow* Window)
{
	for (int i = 0; i < this->Enemies.size(); i++)
	{
		if(this->Enemies[i])
			this->Enemies[i]->Draw(Window);
	}
}

vector<Enemy*> Engine::GamePlay::EnemyManager::GetEnemiesInRange(FloatRect BoundingBox)
{
	vector<Enemy*> ReturnValue;

	for (auto En : this->Enemies)
	{
		FloatRect Tester = FloatRect(En->GetPosition().x, En->GetPosition().y, En->GetSize().x, En->GetSize().y);

		if (Tester.intersects(BoundingBox))
			ReturnValue.push_back(En);
	}

	return ReturnValue;
}
