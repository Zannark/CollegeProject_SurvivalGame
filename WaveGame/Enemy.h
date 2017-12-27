#pragma once

#include <memory>
#include "stlastar.h"
#include "GameTexture.h"
#include "Character.h"
#include "Common.h"
#include "NavigationNode.h"
#include "Player.h"
#include "Map.h"
#include "GameTime.h"

using namespace Engine::Misc;
using namespace Engine::Core;
using namespace std;

#define ENEMY_ATTACK_RANGE 17.f
#define ENEMY_ATTACK_INTERVAL 1.5f
#define ENEMY_MAX_MOVEMENT_SPEED 5.f

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
		Enemy(Vector2f Position, RenderWindow* Window, shared_ptr<Player> P);
		~Enemy();

		void Update(RenderWindow* Window, Map M, float dt);

	private:
		void ManageState(void);
		void FindPath(void);
		void CheckDistance(void);
		void Attack(void);
		Vector2f AlignPlayer(void);

		bool HasStarted;
		bool FinishedPath;
		int SearchState;
		float MovementPercentage;
		int AttackDamage;
		float AttackTimer;
		float MovementSpeed;
		Vector2f NodePosition;
		EnemyState State;
		NavigationNode StartNode;
		NavigationNode EndNode;
		NavigationNode *CurrentNode;
		RenderWindow* Window;
		shared_ptr<Player> P;
		AStarSearch<NavigationNode> Search;
	};
}