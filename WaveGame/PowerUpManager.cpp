#include "PowerUpManager.h"

///The rarity is the previous max rarity + 1 to the current rarities max value.
map<string, int> PowerUpRarities;
bool IsRaritySetUp = false;

///<summary>
///Sets the level of rarity for the different power ups.
///</summary>
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

///<summary>
///This is called once per frame.
///It randomly selects a new power up, every POWER_UP_MANAGER_MINIMUM_SPAWN_LIMIT seconds.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::GamePlay::PowerUpManager::SpawnPowerUps(Player* P, RenderWindow* Wnd, Map M)
{
	if (!IsRaritySetUp)
		SetUpRarities();

	if (this->SpawnedPowerUps.size() < POWER_UP_MANAGER_MAXIMUM_POWER_UP && this->Timer >= POWER_UP_MANAGER_MINIMUM_SPAWN_LIMIT)
	{
		int PreviousRarity = -1;

		for (map<string, int>::iterator It = PowerUpRarities.begin(); It != PowerUpRarities.end(); ++It)
		{
			int SpawnValue = rand() % It->second;
			//Vector2f Position = Vector2f((float)(rand() % (WINDOW_WIDTH - POWER_UP_TEXTURE_SIZE)), (float)(rand() % (WINDOW_HEIGHT - POWER_UP_TEXTURE_SIZE)));

			float X = 0;
			float Y = 0;
			bool HasCollisionOccured = false;

			for (size_t i = 0; i < M.GetProps().size(); i++)
			{
				X = (float)(rand() % (int)(((Wnd->getSize().x - POWER_UP_TEXTURE_SIZE) - POWER_UP_TEXTURE_SIZE + 1) + POWER_UP_TEXTURE_SIZE));
				Y = (float)(rand() % (int)(((Wnd->getSize().y - POWER_UP_TEXTURE_SIZE) - POWER_UP_TEXTURE_SIZE + 1) + POWER_UP_TEXTURE_SIZE));

				for (Prop P : M.GetProps())
				{
					FloatRect PropBoundingBox;
					FloatRect CollisionTesterRect;

					CollisionTesterRect = FloatRect(X, Y, POWER_UP_TEXTURE_SIZE, POWER_UP_TEXTURE_SIZE);
					PropBoundingBox = get<0>(P)->GetSFMLSprite()->getGlobalBounds();
					
					if(CollisionTesterRect.intersects(PropBoundingBox))
						HasCollisionOccured = true;
				}

				if (HasCollisionOccured)
					HasCollisionOccured = false;
				else
					break;
			}

			///SpeedPowerUp
			if (SpawnValue >= (PreviousRarity + 1) && SpawnValue < (++It)->second)
			{
				auto Power = new SpeedPowerUp(Vector2f(X, Y));
				Power->InitBasicPowerUp();
				this->SpawnedPowerUps.push_back(Power);
				this->Timer = 0;
				break;
			}
			///DamagePowerUp
			else if (SpawnValue >= (PreviousRarity + 1))
			{
				auto Power = new DamagePowerUp(Vector2f(X, Y));
				Power->InitBasicPowerUp();
				this->SpawnedPowerUps.push_back(Power);
				this->Timer = 0;
				break;
			}
		}
	}
}

///<summary>
///Called once per frame.
///Handles the spawning and the updating of indiviual power ups.
///Deletes them when no longer needed.
///</summary>
///<param name = "P">A pointer to the player.</param>
///<param name = "dt">Delta time.</param>
void Engine::GamePlay::PowerUpManager::Update(Player * P, RenderWindow* Wnd, Map M, float dt)
{
	this->Timer += dt;
	this->SpawnPowerUps(P, Wnd, M);

	for (size_t i = 0; i < this->SpawnedPowerUps.size(); i++)
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

///<summary>
///Renders the power ups to the screen.
///</summary>
///<param name = "Window">A pointer to the RenderWindow to draw to.</param>
void Engine::GamePlay::PowerUpManager::Draw(RenderWindow * Window)
{
	for (auto PowerUp : this->SpawnedPowerUps)
		PowerUp->Draw(Window);
}
