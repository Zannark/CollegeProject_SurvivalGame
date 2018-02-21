#pragma once

#include <memory>
#include <math.h>
#include <map>
#include <SFML\Graphics.hpp>
#include "Common.h"
#include "Character.h"
#include "GameTexture.h"
#include "Map.h"
#include "SFML_Collision.h"
#include "VectorMaths.h"

using namespace std;
using namespace sf;
using namespace Engine::Core;
using namespace Engine::Misc;

#define PLAYER_ATTACK_INTERVAL 0.25f
#define PLAYER_MAX_ATTACK_DAMAGE 7
#define PLAYER_MAX_HEALTH 200

namespace Engine::GamePlay
{
	class Player : public Character
	{
	public:
		Player();
		~Player();

		void Update(RenderWindow* Window, Map M, float dt) override;
		void SetEnemyManager(void* Manager);
		void SetFullHealth(void);
		void RegenHalfMissingHealth(void);
		void DrawUI(RenderWindow* Window);
		void DrawWeapon(RenderWindow* Window);
		void SetSpeedModifier(float Modifier);
		void SetDamageModifier(int Modifier);
		void SetPowerUp(void* Power);

		bool HasPowerUp(void) const;
		shared_ptr<GameTexture> GetPlayerWeapon(void) const;

	protected:
		void UpdateUI(void);

	private:
		void Attack(void);
		void HandleMovement(RenderWindow* Window, Map M, float dt);
		void HandleRotation(RenderWindow* Window, float dt);
		void SetPowerUpText(string PowerUpName);
		bool CheckCollision(Map M);

		int OldHealth;
		float MovementSpeed;
		float MovementSpeedModifer;
		float AttackTimer;
		int AttackDamageModifier;
		void* Manager;

		shared_ptr<GameTexture> PlayerWeapon;
		RectangleShape HealthBar;
		RectangleShape HealthBarOutLine;

		void* PowerUp;
		string PowerUpName;
		Font PowerUpFont;
		Text PowerUpText;
	};
}


