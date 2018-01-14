#pragma once

#include "PowerUpBase.h"
#include "Player.h"
#include "GameTexture.h"

using namespace Engine::Core;

#define SPEED_BOOST_MULTIPLIER 1.5f

namespace Engine::GamePlay 
{
	class SpeedPowerUp : public PowerUpBase
	{
	public:
		SpeedPowerUp(Vector2f Position);
		~SpeedPowerUp() = default;

		virtual void OnUse(Player* P) override;
		virtual void OnUseEnd(Player* P) override;
		//virtual void Update(Player* P, float dt) override;
	};
}

