#include "NavigationNode.h"

namespace
{
	///A 2-D dynamnic array of all the navigation nodes on the screen.
	vector<vector<shared_ptr<Engine::Core::NavigationNode>>> NavigationMesh;
}

///<summary>
///Generates a mesh of navigation nodes across the map.
///They're evenly distrubuted at a distance of NAVIGATION_NODE_DISTANCE from each other.
///</summary>
///<param name = "Window">A pointer to the RenderWindow used.</param>
///<param name = "P">A copy of the currently used Player object.</param>
///<param name = "M">A copy of the map which is currently being used.</param>
void Engine::Core::CreateNavigationMesh(RenderWindow* Window, Player P, Map M)
{
	///For ease
	const float Width = (float)Window->getSize().x;
	const float Height = (float)Window->getSize().y;
	auto Props = M.GetProps();
	float x = 0;
	float y = 0;

	for (float i = 0; x < Width; i++)
	{
		NavigationMesh.push_back(vector<shared_ptr<NavigationNode>>());
		y = 0;

		for (float j = 0; y < Height; j++)
		{
			FloatRect Tester = FloatRect(x, y, 1.0f, 1.0f);
			bool DoesCollision = false;

			for (auto P : Props)
			{
				if (get<0>(P)->GetSFMLSprite()->getGlobalBounds().intersects(Tester))
				{
					DoesCollision = get<1>(P);
					break;
				}
			}

			NavigationMesh[(size_t)i].push_back(make_shared<NavigationNode>(x, y, Window, DoesCollision));
			y += NAVIGATION_NODE_DISTANCE;
		}

		x += NAVIGATION_NODE_DISTANCE;
	}
}

///<summary>
///Gets a node at a certain position. 
///</summary>
///<param name = "Position">The position to get the node at.</param>
///<returns>A pointer to the NavigationNode at the given position.</returns>
shared_ptr<NavigationNode> Engine::Core::GetNodeByPosition(Vector2f Position)
{
	size_t x = (size_t)(Position.x / NAVIGATION_NODE_DISTANCE);
	size_t y = (size_t)(Position.y / NAVIGATION_NODE_DISTANCE);
	
	return GetNodeByCell(Vector2u(x, y));
}

///<summary>
///Gets the position of a navigation node by a given cell position.
///</summary>
///<param name = "Cell">The position of the cell to get the node from.</param>
///<returns>A smart pointer to the navigation node, nullptr if there isn't one.</returns>
shared_ptr<NavigationNode> Engine::Core::GetNodeByCell(Vector2u Cell)
{
	if (Cell.x >= NavigationMesh.size() || Cell.y >= NavigationMesh[0].size())
		return nullptr;

	return NavigationMesh[Cell.x][Cell.y];
}

Engine::Core::NavigationNode::NavigationNode(Vector2f Position, RenderWindow* Window, bool DoesCollision)
{
	this->Position = Position;
	this->Window = Window;
	this->DoesCollision = DoesCollision;
}

Engine::Core::NavigationNode::NavigationNode(float x, float y, RenderWindow* Window, bool DoesCollision)
{
	this->Position = Vector2f(x, y);
	this->DoesCollision = DoesCollision;
	this->Window = Window;
}

///<summary>
///Gets the estimated distance between the nodes position and the goal node.
///</summary>
///<param name = "GoalNode">The goal node.</param>
///<returns>The estimated distance between nodes.</returns>
float Engine::Core::NavigationNode::GoalDistanceEstimate(NavigationNode& GoalNode)
{
	return EuclideanDistance(GoalNode.Position, this->Position);
}

///<summary>
///Checks if the current node is the goal node.
///</summary>
///<param name = "GoalNode">The goal node.</param>
///<returns>True if it is the goal, false otherwise.</returns>
bool Engine::Core::NavigationNode::IsGoal(NavigationNode& GoalNode)
{
	return this->IsSameState(GoalNode);
}

///<summary>
///Gets the nodes next to this one. In all directions.
///</summary>
///<param name = "AStarSearch">A pointer to the A* search algorithm.</param>
///<param name = "ParentNode">The parent node, after this one.</param>
///<returns>True, requirement of library to have a boolean return value. Not used in this case.</returns>
bool Engine::Core::NavigationNode::GetSuccessors(AStarSearch<NavigationNode>* AStarSearch, NavigationNode* ParentNode)
{
	auto AddSuccessor = [this, AStarSearch, ParentNode](Vector2f SuccessorPos)
	{
		auto Node = GetNodeByPosition(SuccessorPos);
		if (Node && (!ParentNode || !Node->IsSameState(*ParentNode)))
			AStarSearch->AddSuccessor(*Node);

		if (Node && AStarSearch->GetSolutionEnd())
		{
			if (Node->IsGoal(*AStarSearch->GetSolutionEnd()))
				AStarSearch->AddSuccessor(*Node);
		}
	};

	AddSuccessor(this->Position + Vector2f(-NAVIGATION_NODE_DISTANCE, 0)); ///Left
	AddSuccessor(this->Position + Vector2f(0, -NAVIGATION_NODE_DISTANCE)); ///Up
	AddSuccessor(this->Position + Vector2f(NAVIGATION_NODE_DISTANCE, 0));  ///Right
	AddSuccessor(this->Position + Vector2f(0, NAVIGATION_NODE_DISTANCE));  ///Down

	AddSuccessor(this->Position + Vector2f(-NAVIGATION_NODE_DISTANCE, -NAVIGATION_NODE_DISTANCE)); ///Up Left
	AddSuccessor(this->Position + Vector2f(-NAVIGATION_NODE_DISTANCE, NAVIGATION_NODE_DISTANCE)); ///Down Left
	AddSuccessor(this->Position + Vector2f(NAVIGATION_NODE_DISTANCE, -NAVIGATION_NODE_DISTANCE));  ///Up Right
	AddSuccessor(this->Position + Vector2f(NAVIGATION_NODE_DISTANCE, NAVIGATION_NODE_DISTANCE));  ///Down Right

	return true;
}

///<summary>
///Calulates the cose of traveling from this node to a neighboring node.
///</summary>
///<param name = "Successor">The neighboring node.</param>
///<returns>The cost of the traveling.</returns>
float Engine::Core::NavigationNode::GetCost(NavigationNode& Successor)
{
	///A high cost is returned so the enemies will avoid it.
	const float CollisionCost = 100000000.f;

	if (this->DoesCollision)
		return CollisionCost;
	
	return fabsf(EuclideanDistance(this->Position, Successor.Position));
}

///<summary>
///Checks if two nodes are the same state.
///</summary>
///<param name = "OtherNode">The node to test against.</param>
///<returns>True if they're the same state, false otherwise.</returns>
bool Engine::Core::NavigationNode::IsSameState(NavigationNode& OtherNode)
{
	return (((int)floorf(this->Position.x) == (int)floorf(OtherNode.Position.x)) && ((int)floorf(this->Position.y) == (int)floorf(OtherNode.Position.y)));
}

///<summary>
///Gets if a navigation node does collision.
///</summary>
///<returns>True if the node does collision, otherwise false.</returns>
bool Engine::Core::NavigationNode::GetCollision(void) const
{
	return this->DoesCollision;
}

///<summary>
///Sets if the navigation node does collision to a given value.
///</summary>
///<param name = "Collides">The value to set DoesCollision to. True if the node does collision, otherwise false.</param>
void Engine::Core::NavigationNode::SetCollision(bool Collides)
{
	this->DoesCollision = Collides;
}