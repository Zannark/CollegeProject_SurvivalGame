#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <vector>
#include <map>
#include "Player.h"
#include "PowerUpBase.h"
#include "SpeedPowerUp.h"
#include "DamagePowerUp.h"

using namespace std;
using namespace sf;
using namespace Engine::Core;

#define POWER_UP_MANAGER_MINIMUM_SPAWN_LIMIT 10.0f //Seconds
#define POWER_UP_MANAGER_MAXIMUM_POWER_UP 3
#define POWER_UP_TEXTURE_SIZE 32

namespace Engine::GamePlay
{
	///<summary>
	///The object which is resposible for controlling all of the powerups in the game.
	///</summary>
	class PowerUpManager
	{
	public:
		PowerUpManager();
		~PowerUpManager() = default;

		void SpawnPowerUps(Player* P, RenderWindow* Wnd, Map M);
		void Update(Player* P, RenderWindow* Wnd, Map M, float dt);
		void Draw(RenderWindow* Window);

	private:
		vector<PowerUpBase*> SpawnedPowerUps;
		float Timer;
	};
}