#pragma once

#include "PowerUpBase.h"

using namespace Engine::Core;

#define DAMAGE_BOOST_MULTIPLIER 2

namespace Engine::GamePlay
{
	class DamagePowerUp : public PowerUpBase
	{
	public:
		DamagePowerUp(Vector2f Position);
		~DamagePowerUp() = default;

		virtual void OnUse(Player* P) override;
		virtual void OnUseEnd(Player* P) override;
	};
}