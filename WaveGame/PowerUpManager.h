#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "PowerUpBase.h"
#include "SpeedPowerUp.h"

using namespace std;
using namespace sf;
using namespace Engine::Core;

#define POWER_UP_MANAGER_MINIMUM_SPAWN_LIMIT 10.0f //Seconds
#define POWER_UP_MANAGER_MAXIMUM_POWER_UP 4

namespace Engine::GamePlay
{
	class PowerUpManager
	{
	public:
		PowerUpManager();
		~PowerUpManager() = default;

		void SpawnPowerUps(void);
		void Update(Player* P, float dt);
		void Draw(RenderWindow* Window);

	private:
		vector<PowerUpBase*> SpawnedPowerUps;
		float Timer;
	};
}