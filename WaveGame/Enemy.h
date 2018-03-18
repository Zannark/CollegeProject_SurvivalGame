#pragma once

#include <memory>
#include <random>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "stlastar.h"
#include "Character.h"
#include "Common.h"
#include "NavigationNode.h"
#include "Player.h"
#include "Map.h"
#include "GameTime.h"

using namespace Engine::Misc;
using namespace Engine::Core;
using namespace std;

#define ENEMY_ATTACK_RANGE 32.f
#define ENEMY_ATTACK_INTERVAL 0.75f
#define ENEMY_MAX_ATTACK 10
#define ENEMY_MIN_ATTACK 1
#define ENEMY_MAX_MOVEMENT_SPEED 4.5f
#define ENEMY_MIN_MOVEMENT_SPEED 0.45f
#define ENEMY_MAX_HEALTH 15
#define ENEMY_RECIEVE_DAMAGE_COLOUR_CHANGE_LENGTH 0.1f ///Seconds

namespace Engine::GamePlay
{
	enum EnemyState
	{
		Pathfinding = 0,
		CheckDistance,
		Attacking
	};

	class Enemy : public Character
	{
	public:
		Enemy(Vector2f Position, RenderWindow* Window, Player* P, float Speed);
		~Enemy();

		void Update(RenderWindow* Window, Map M, float dt) override;
		void TakeDamage(int Amount) override;

	private:
		void ManageState(void);
		void FindPath(void);
		void CheckDistance(void);
		void Attack(void);

		bool HasStarted;
		int SearchState;
		float MovementPercentage;
		float AttackTimer;
		float MovementSpeed;
		Vector2f NodePosition;
		EnemyState State;
		NavigationNode StartNode;
		NavigationNode EndNode;
		NavigationNode *CurrentNode;
		RenderWindow* Window;
		Player* P;
		AStarSearch<NavigationNode> Search;
		Color RecieveDamageColour;
		Color DefaultColour;
		float ColourChangeTimer;
	};
}

