#include "PowerUpManager.h"

///The rarity is the previous max rarity + 1 to the current rarities max value.
map<string, int> PowerUpRarities;
bool IsRaritySetUp = false;

void SetUpRarities(void)
{
	IsRaritySetUp = true;

	PowerUpRarities["Speed Boost"] = 10;
	PowerUpRarities["Damage Boost"] = 15;
}

Engine::GamePlay::PowerUpManager::PowerUpManager()
{
	this->Timer = 0;
}

void Engine::GamePlay::PowerUpManager::SpawnPowerUps(Player* P)
{
	if (!IsRaritySetUp)
		SetUpRarities();

	if (this->SpawnedPowerUps.size() < POWER_UP_MANAGER_MAXIMUM_POWER_UP && this->Timer >= POWER_UP_MANAGER_MINIMUM_SPAWN_LIMIT)
	{
		int PreviousRarity = -1;

		for (map<string, int>::iterator It = PowerUpRarities.begin(); It != PowerUpRarities.end(); ++It)
		{
			int SpawnValue = rand() % It->second;
			Vector2f Position = Vector2f((float)(rand() % (WINDOW_WIDTH - POWER_UP_TEXTURE_SIZE)), (float)(rand() % (WINDOW_HEIGHT - POWER_UP_TEXTURE_SIZE)));

			cout << "Needed : " << PreviousRarity % 1 << " | Got : " << SpawnValue << endl;

			///SpeedPowerUp
			if (SpawnValue >= (PreviousRarity + 1))
			{
				auto Power = new SpeedPowerUp(Position);
				Power->InitBasicPowerUp();
				this->SpawnedPowerUps.push_back(Power);
				this->Timer = 0;
				break;
			}
			else if (SpawnValue >= (PreviousRarity + 1))
			{
				auto Power = new DamagePowerUp(Position);
				Power->InitBasicPowerUp();
				this->SpawnedPowerUps.push_back(Power);
				this->Timer = 0;
				break;
			}
		}
	}
}

void Engine::GamePlay::PowerUpManager::Update(Player * P, float dt)
{
	this->Timer += dt;
	this->SpawnPowerUps(P);

	for (int i = 0; i < this->SpawnedPowerUps.size(); i++)
	{
		if(!this->SpawnedPowerUps[i]->GetNeedsToBeDestroyed())
			this->SpawnedPowerUps[i]->Update(P, dt);
		else
		{
			delete this->SpawnedPowerUps[i];
			this->SpawnedPowerUps.erase(this->SpawnedPowerUps.begin() + i);
		}
	}
}

void Engine::GamePlay::PowerUpManager::Draw(RenderWindow * Window)
{
	for (auto PowerUp : this->SpawnedPowerUps)
		PowerUp->Draw(Window);
}
