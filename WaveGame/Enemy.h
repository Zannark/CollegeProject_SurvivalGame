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
		Enemy(Vector2f Position, shared_ptr<RenderWindow> Window, shared_ptr<Player> P);
		~Enemy();

		void Update(shared_ptr<RenderWindow> Window, Map M, float dt);

	private:
		void ManageState(void);
		void FindPath(void);

		bool HasStarted;
		bool FinishedPath;
		int SearchState;
		float MovementPercentage;
		Vector2f NodePosition;
		EnemyState State;
		NavigationNode StartNode;
		NavigationNode EndNode;
		NavigationNode *CurrentNode;
		shared_ptr<RenderWindow> Window;
		shared_ptr<Player> P;
		AStarSearch<NavigationNode> Search;
	};
}