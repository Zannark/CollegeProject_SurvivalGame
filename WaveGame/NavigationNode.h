#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include "stlastar.h"
#include "Common.h"
#include "Map.h"
#include "Player.h"

using namespace sf;
using namespace Engine::Misc; 
using namespace Engine::GamePlay;

#define NAVIGATION_NODE_DISTANCE 32 ///The distance inbetween (in pixels) the navigation nodes. 

namespace Engine::Core
{
	class NavigationNode
	{
	public:
		NavigationNode() = default;
		NavigationNode(Vector2f Position, RenderWindow* Window, bool DoesCollision);
		NavigationNode(float x, float y, RenderWindow* Window, bool DoesCollision);

		float GoalDistanceEstimate(NavigationNode &nodeGoal);
		bool IsGoal(NavigationNode &nodeGoal);
		bool GetSuccessors(AStarSearch<NavigationNode> *astarsearch, NavigationNode *parent_node);
		float GetCost(NavigationNode &successor);
		bool IsSameState(NavigationNode &rhs);
		
		Vector2f Position;
		RenderWindow* Window;

	private:
		bool DoesCollision;
	};

	extern void CreateNavigationMesh(RenderWindow* Window, Player P, Map M);
	extern shared_ptr<NavigationNode> GetNodeByPosition(Vector2f Position);
	extern void DrawNavigationMesh(RenderWindow* Window);
}

