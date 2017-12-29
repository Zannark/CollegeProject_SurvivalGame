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
#define PLAYER_MAX_ATTACK_DAMAGE 5
#define PLAYER_MAX_HEALTH 20

namespace Engine::GamePlay
{
	class Player : public Character
	{
	public:
		Player();
		~Player();

		void Update(RenderWindow* Window, Map M, float dt) override;
		void SetEnemyManager(void* Manager);

		void DrawUI(RenderWindow* Window);
		void DrawWeapon(RenderWindow* Window);
	protected:
		virtual void UpdateUI(void) override;

	private:
		void Attack(void);
		void HandleMovement(RenderWindow* Window, Map M, float dt);
		void HandleRotation(RenderWindow* Window, float dt);
		bool CheckCollision(Map M);

		float MovementSpeed;
		RectangleShape PlayerWeapon;
		void* Manager;

		RectangleShape HealthBar;
		RectangleShape HealthBarOutLine;
	};
}
