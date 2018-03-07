#include "NavigationNode.h"

namespace
{
#if _DEBUG
	bool SetupShape = true;
	RectangleShape DebugShapeNonCollision;
	RectangleShape DebugShapeCollision;
#endif
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
	int Count = 0;

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
				if (P->GetSFMLSprite()->getGlobalBounds().intersects(Tester))
				{
					DoesCollision = true;
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
	shared_ptr<NavigationNode> ReturnValue;
	auto WindowSize = NavigationMesh[0][0]->Window->getSize();

	size_t x = (size_t)(Position.x / NAVIGATION_NODE_DISTANCE);
	size_t y = (size_t)(Position.y / NAVIGATION_NODE_DISTANCE);
	
	if (x >= NavigationMesh.size() || y >= NavigationMesh[0].size())
		return nullptr;

	return NavigationMesh[x][y];
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
	return (this->Position == GoalNode.Position);
}

///<summary>
///Gets the nodes next to this one. In all directions.
///</summary>
///<param name = "AStarSearch">A pointer to the A* search algorithm.</param>
///<param name = "ParentNode">The parent node, after this one.</param>
///<returns>True, requirement of library to have a boolean return value. Not used in this case.</returns>
bool Engine::Core::NavigationNode::GetSuccessors(AStarSearch<NavigationNode>* AStarSearch, NavigationNode* ParentNode)
{
	auto HandlePathfindingCollision = [](Vector2f Position) -> bool
	{
		shared_ptr<NavigationNode> NeighbourNode = GetNodeByPosition(Position);
		if ((NeighbourNode && NeighbourNode->GetCollision()))
			return true;
		return false;
	};

	auto AddSuccessor = [this, AStarSearch, ParentNode, HandlePathfindingCollision](Vector2f SuccessorPos)
	{
		auto Node = GetNodeByPosition(SuccessorPos);
		if (!Node)
			return;

		bool IsNearCollisionNode = (HandlePathfindingCollision(Vector2f(Node->Position.x + NAVIGATION_NODE_DISTANCE, 0)) || ///Node to the right
			HandlePathfindingCollision(Vector2f(Node->Position.x - NAVIGATION_NODE_DISTANCE, 0)) || ///Node to the left
			HandlePathfindingCollision(Vector2f(0, Node->Position.y + NAVIGATION_NODE_DISTANCE)) || ///Node below
			HandlePathfindingCollision(Vector2f(0, Node->Position.y - NAVIGATION_NODE_DISTANCE)) || ///Node above

			HandlePathfindingCollision(Vector2f(Node->Position.x + NAVIGATION_NODE_DISTANCE, Node->Position.y + NAVIGATION_NODE_DISTANCE)) || ///Node to the right and below
			HandlePathfindingCollision(Vector2f(Node->Position.x - NAVIGATION_NODE_DISTANCE, Node->Position.y + NAVIGATION_NODE_DISTANCE)) || ///Node to the left and below
			HandlePathfindingCollision(Vector2f(Node->Position.x + NAVIGATION_NODE_DISTANCE, Node->Position.y - NAVIGATION_NODE_DISTANCE)) || ///Node to the right and up
			HandlePathfindingCollision(Vector2f(Node->Position.x - NAVIGATION_NODE_DISTANCE, Node->Position.y - NAVIGATION_NODE_DISTANCE)) || ///Node to the left and up

			HandlePathfindingCollision(Vector2f(Node->Position.x + (NAVIGATION_NODE_DISTANCE * 2), 0)) || ///Node to the right, NAVIGATION_NODE_DISTANCE * 2
			HandlePathfindingCollision(Vector2f(Node->Position.x - (NAVIGATION_NODE_DISTANCE * 2), 0)) || ///Node to the left, NAVIGATION_NODE_DISTANCE * 2
			HandlePathfindingCollision(Vector2f(0, Node->Position.y + (NAVIGATION_NODE_DISTANCE * 2))) || ///Node below, NAVIGATION_NODE_DISTANCE * 2
			HandlePathfindingCollision(Vector2f(0, Node->Position.y - (NAVIGATION_NODE_DISTANCE * 2))) || ///Node above, NAVIGATION_NODE_DISTANCE * 2

			HandlePathfindingCollision(Vector2f(Node->Position.x + (NAVIGATION_NODE_DISTANCE * 2), Node->Position.y + (NAVIGATION_NODE_DISTANCE * 2))) || ///Node to the right and below, NAVIGATION_NODE_DISTANCE * 2
			HandlePathfindingCollision(Vector2f(Node->Position.x - (NAVIGATION_NODE_DISTANCE * 2), Node->Position.y + (NAVIGATION_NODE_DISTANCE * 2))) || ///Node to the left and below, NAVIGATION_NODE_DISTANCE * 2
			HandlePathfindingCollision(Vector2f(Node->Position.x + (NAVIGATION_NODE_DISTANCE * 2), Node->Position.y - (NAVIGATION_NODE_DISTANCE * 2))) || ///Node to the right and up, NAVIGATION_NODE_DISTANCE * 2
			HandlePathfindingCollision(Vector2f(Node->Position.x - (NAVIGATION_NODE_DISTANCE * 2), Node->Position.y - (NAVIGATION_NODE_DISTANCE * 2))));///Node to the left and up, NAVIGATION_NODE_DISTANCE * 2

		if ((!ParentNode || !Node->IsSameState(*ParentNode) || (Node->GetCollision() && IsNearCollisionNode)))
			AStarSearch->AddSuccessor(*Node);
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

	if (false)
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

bool Engine::Core::NavigationNode::GetCollision(void) const
{
	return this->DoesCollision;
}

void Engine::Core::DrawNavigationMesh(RenderWindow* Window)
{
#if _DEBUG
	if (SetupShape)
	{
		SetupShape = false;
		DebugShapeNonCollision.setFillColor(Color(128, 128, 128, 255));
		DebugShapeNonCollision.setOutlineThickness(1);
		DebugShapeNonCollision.setOutlineColor(Color(0, 0, 0, 255));
		DebugShapeNonCollision.setSize(Vector2f(3, 3));

		DebugShapeCollision.setFillColor(Color::Red);
		DebugShapeCollision.setOutlineThickness(1);
		DebugShapeCollision.setOutlineColor(Color(0, 0, 0, 255));
		DebugShapeCollision.setSize(Vector2f(3, 3));
	}

	for (unsigned int k = 0; k < NavigationMesh.size(); k++)
	{
		for (unsigned int j = 0; j < NavigationMesh[k].size(); j++)
		{	
			if(NavigationMesh[k][j]->GetCollision())
				DebugShapeCollision.setPosition(NavigationMesh[k][j]->Position);
			else
				DebugShapeNonCollision.setPosition(NavigationMesh[k][j]->Position);
			Window->draw(DebugShapeNonCollision);
			Window->draw(DebugShapeCollision);
		}
	}
#endif
}