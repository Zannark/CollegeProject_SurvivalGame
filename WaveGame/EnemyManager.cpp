#include "EnemyManager.h"

Engine::GamePlay::EnemyManager::EnemyManager(RenderWindow * Window, shared_ptr<Player> P, mt19937* Generator)
{
	this->CurrentWave = 0;
	this->State = MatchState::NewMatch;
	this->P = P;
	this->IntervalTimer = 0.f;
	this->RoundNumber = 1;
	this->RandomNumber = uniform_real_distribution<float>(ENEMY_MIN_MOVEMENT_SPEED, ENEMY_MAX_MOVEMENT_SPEED);
	this->Generator = Generator;
	this->RoundMessage = to_string(this->RoundNumber);
	this->RoundFont.loadFromFile("Assets/Heavy_Data.ttf");
	this->RoundText.setFont(this->RoundFont);
	this->RoundText.setColor(Color::Black);
	this->RoundText.setString("Round: " + this->RoundMessage);
	this->RoundText.setPosition(Vector2f(645, 0));
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
			this->RoundNumber += 1;
			this->RoundMessage = to_string(this->RoundNumber);
			this->RoundText.setPosition(Vector2f(645, 0));
			this->RoundText.setString("Round: " + this->RoundMessage);

			this->IntervalTimer = 0;
			this->State = MatchState::NewMatch;
			return;
		}

		this->RoundText.setPosition(Vector2f(590, 0));
		this->RoundText.setString("Round Interval");
		this->IntervalTimer += dt;
	}
	else if (this->State == MatchState::NewMatch)
	{
		this->Enemies = vector<Enemy*>();
		P->RegenHalfMissingHealth();

		for (int i = 0; i < (DEFAULT_ENEMY_COUNT + CurrentWave); i++)
		{
			float x = (float)(rand() % Window->getSize().x);
			float y = (float)(rand() % Window->getSize().y);

			this->Enemies.push_back(new Enemy(Vector2f(x, y), Window, this->P, this->RandomNumber(*this->Generator)));
		}

		this->State = MatchState::InMatch;
	}		
}

void Engine::GamePlay::EnemyManager::Draw(RenderWindow* Window)
{
	Window->draw(this->RoundText);

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
		if (Collision::BoundingBoxTest(*P->GetPlayerWeapon()->GetSFMLSprite(), *En->GetGameTexure()->GetSFMLSprite()))
			ReturnValue.push_back(En);
	}

	return ReturnValue;
}
