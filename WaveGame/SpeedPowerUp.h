#pragma once

#include "PowerUpBase.h"
#include "Player.h"
#include "Animator.h"

using namespace Engine::Core;

#define SPEED_BOOST_MULTIPLIER 2.5f

namespace Engine::GamePlay 
{
	///<summary>
	///The powerup which is responisble for increasing and decreasing the speed of the player.
	///</summary>
	class SpeedPowerUp : public PowerUpBase
	{
	public:
		SpeedPowerUp(Vector2f Position);
		~SpeedPowerUp() = default;

		virtual void OnUse(Player* P) override;
		virtual void OnUseEnd(Player* P) override;
	};
}

