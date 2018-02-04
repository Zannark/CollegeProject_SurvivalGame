#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "Player.h"
#include "SFML_Collision.h"

using namespace Engine::GamePlay;

namespace Engine::Core
{
	class PowerUpBase
	{
	public:
		PowerUpBase() = default;
		~PowerUpBase() = default;

		virtual void OnUse(Player* P);
		virtual void OnUseEnd(Player* P);
		virtual void Update(Player* P, float dt);
		void Draw(RenderWindow* Wnd);
		void InitBasicPowerUp(void);
		void SetNeedsToBeDestroyed(void);
		bool GetNeedsToBeDestroyed(void);
		bool GetCollected(void);

	protected:
		shared_ptr<GameTexture> Texture;
		bool HasBeenCollected; //Has the power up been picked up yet?
		bool NeedsToBeDestroyed; //A flag for if the time is up.
		bool HasBeenUsed;
		float ActiveTime; //How long the power up is active for after being picked up (int seconds).
		float Timer;
		string PowerUpName;
	};
}

