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

namespace Engine::GamePlay
{
	enum MatchState
	{
		InMatch = 0,
		Interval,
		NewMatch
	};

	class EnemyManager
	{
	public:
		EnemyManager(RenderWindow* Window, shared_ptr<Player> P);
		~EnemyManager();

		void Update(RenderWindow* Window, Map M, float dt);
		void Draw(RenderWindow* Window);

		//vector<Enemy*> GetEnemiesInRange(FloatRect BoundingBox);

	private:
		shared_ptr<Player> P;
		vector<Enemy*> Enemies;
		int CurrentWave;
		int IntervalTimer;
		MatchState State;
	};

	class Player : public Character
	{
	public:
		Player();
		~Player();

		void Update(RenderWindow* Window, Map M, float dt) override;
		void TakeDamage(int Amount);
		void SetEnemyManager(EnemyManager* Manager);
		
	private:
		void Attack(void);
		void HandleMovement(RenderWindow* Window, Map M, float dt);
		void HandleRotation(RenderWindow* Window, float dt);
		bool CheckCollision(Map M);
		bool CheckHealth(void);

		float MovementSpeed;
		RectangleShape PlayerWeapon;
		EnemyManager* Manager;
	};
}
