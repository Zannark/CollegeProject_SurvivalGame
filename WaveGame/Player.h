#pragma once

#include <memory>
#include <math.h>
#include <map>
#include <tuple>
#include <algorithm>
#include <stdlib.h>
#include <SFML\Graphics.hpp>
#include "Common.h"
#include "Character.h"
#include "Animator.h"
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
#define PLAYER_HIGH_HEALTH_THRESHOLD 150 ///<= 75% of 200
#define PLAYER_MEDIUM_HEALTH_THRESHOLD 50 ///> 75% && <= 25% of 200
///No need for a low threshold definition, is low health when below PLAYER_MEDIUM_HEALTH_THRESHOLD.

namespace Engine::GamePlay
{
	using PlayerCollisionResult = tuple<bool, shared_ptr<Animator>>;

	enum class PlayerMovementDirection
	{
		Up = (1 << 0),
		Down = (1 << 1),
		Left = (1 << 2),
		Right = (1 << 3),
		Stationary = (1 << 4)
	};

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
		
		
		shared_ptr<Animator> GetPlayerWeapon(void) const;

	protected:
		void UpdateUI(void);

	private:
		void Attack(void);
		void HandleMovement(RenderWindow* Window, Map M, float dt);
		void HandleRotation(RenderWindow* Window, float dt);
		void HandleCollision(Map M, float MovementOffset);
		void SetPowerUpText(string PowerUpName);
		void CalculateDirection(void);
		PlayerCollisionResult CheckCollision(Map M);

		int AttackDamageModifier;
		int OldHealth;
		float MovementSpeed;
		float MovementSpeedModifer;
		float AttackTimer;
		void* Manager;

		PlayerMovementDirection MovementDirection;
		Vector2f PreviousFramePosition;
		shared_ptr<Animator> PlayerWeapon;
		shared_ptr<Animator> HealthBarIcon;
		RectangleShape HealthBar;
		RectangleShape HealthBarOutLine;

		void* PowerUp;
		string PowerUpName;
		Font PowerUpFont;
		Text PowerUpText;

		map<PlayerMovementDirection, bool> CanMoveDirection;

		Color HighHealthColour;
		Color MediumHealthColour;
		Color LowHealthColour;
	};
}


