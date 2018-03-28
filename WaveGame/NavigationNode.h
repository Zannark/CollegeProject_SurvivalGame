#pragma once

#include <SFML\Graphics.hpp>
#include <memory>
#include <vector>
#include <limits>
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
	///<summary>
	///A node which is used for the A* pathfinding.
	///Represents a single point on the screen.
	///</summary>
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
		bool GetCollision(void) const;
		void SetCollision(bool Collides);
		
		Vector2f Position;
		RenderWindow* Window;

	private:
		bool DoesCollision;
	};

	extern void CreateNavigationMesh(RenderWindow* Window, Player P, Map M);
	extern shared_ptr<NavigationNode> GetNodeByPosition(Vector2f Position);
	extern shared_ptr<NavigationNode> GetNodeByCell(Vector2u Cell);
}

