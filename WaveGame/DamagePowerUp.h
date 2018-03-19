#pragma once

#include "PowerUpBase.h"

using namespace Engine::Core;

#define DAMAGE_BOOST_MULTIPLIER 2

namespace Engine::GamePlay
{
	///<summary>
	///The powerup which is responsible for increasing the attack damage of the player.
	///</summary>
	class DamagePowerUp : public PowerUpBase
	{
	public:
		DamagePowerUp(Vector2f Position);
		~DamagePowerUp() = default;

		virtual void OnUse(Player* P) override;
		virtual void OnUseEnd(Player* P) override;
	};
}