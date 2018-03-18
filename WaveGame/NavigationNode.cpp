#include "NavigationNode.h"

namespace
{
#if _DEBUG
	bool SetupShape = true;
	RectangleShape DebugShapeNonCollision;
	RectangleShape DebugShapeCollision;
	RectangleShape DebugShapeNearCollision;
#endif
	vector<vector<shared_ptr<Engine::Core::NavigationNode>>> NavigationMesh;


	///TODO: Probably should think of a better name.
	void SetCollisionOnNodes(void)
	{
		shared_ptr<NavigationNode> NeighbourNode;

		auto HandleNodeCollision = [NeighbourNode](shared_ptr<NavigationNode> ThisNode, Vector2f NodePosition) mutable
		{
			NeighbourNode = GetNodeByPosition(NodePosition);
			if ((NeighbourNode && NeighbourNode->GetCollision()))
				ThisNode->SetIsNearCollision(true);
		};

		///Loop for the multiplier on how far out it goes.
		for (size_t i = 1; i < 2; i++)
		{
			///Loop over each node which is near this one.
			///Go over each row of NavigationNodes.
			for (size_t NodeXPosition = 0; NodeXPosition < NavigationMesh.size(); NodeXPosition++)
			{
				///Go over each node in the row.
				for (size_t NodeYPosition = 0; NodeYPosition < NavigationMesh[NodeXPosition].size(); NodeYPosition++)
				{
					shared_ptr<NavigationNode> ThisNode = GetNodeByCell(Vector2u((unsigned int)NodeXPosition, (unsigned int)NodeYPosition));
					if (!ThisNode)
						continue;
					
					///Go over each direction with ThisNode->Position * i. Eight Lines of glory!
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x + (NAVIGATION_NODE_DISTANCE * i), ThisNode->Position.y)); ///Right
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x - (NAVIGATION_NODE_DISTANCE * i), ThisNode->Position.y)); ///Left
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x, ThisNode->Position.y + (NAVIGATION_NODE_DISTANCE * i))); ///Down
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x, ThisNode->Position.y - (NAVIGATION_NODE_DISTANCE * i))); ///Up

					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x + (NAVIGATION_NODE_DISTANCE * i), ThisNode->Position.y + (NAVIGATION_NODE_DISTANCE * i))); ///Right Down
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x - (NAVIGATION_NODE_DISTANCE * i), ThisNode->Position.y + (NAVIGATION_NODE_DISTANCE * i))); ///Left Down
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x + (NAVIGATION_NODE_DISTANCE * i), ThisNode->Position.y - (NAVIGATION_NODE_DISTANCE * i))); ///Right Up
					HandleNodeCollision(ThisNode, Vector2f(ThisNode->Position.x - (NAVIGATION_NODE_DISTANCE * i), ThisNode->Position.y - (NAVIGATION_NODE_DISTANCE * i))); ///Left Up
				}
			}
		}
	}
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

	//SetCollisionOnNodes();
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
	this->IsNearCollision = false;
}

Engine::Core::NavigationNode::NavigationNode(float x, float y, RenderWindow* Window, bool DoesCollision)
{
	this->Position = Vector2f(x, y);
	this->DoesCollision = DoesCollision;
	this->Window = Window;
	this->IsNearCollision = false;
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
	return this->IsSameState(GoalNode);//(this->Position == GoalNode.Position);
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
		//&& !Node->GetCollision() && !Node->GetIsNearCollision()
		if (Node && (!ParentNode || !Node->IsSameState(*ParentNode)))
			AStarSearch->AddSuccessor(*Node);

		/*if (Node && AStarSearch->GetSolutionEnd())
		{
			if (Node->IsGoal(*AStarSearch->GetSolutionEnd()))
				AStarSearch->AddSuccessor(*Node);
		}*/
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

	//if (false)
		//return CollisionCost;

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

void Engine::Core::NavigationNode::SetCollision(bool Collides)
{
	this->DoesCollision = Collides;
}

bool Engine::Core::NavigationNode::GetIsNearCollision(void) const
{
	return this->IsNearCollision;
}

void Engine::Core::NavigationNode::SetIsNearCollision(bool NearCollision)
{
	if(!this->DoesCollision)
		this->IsNearCollision = NearCollision;
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

		DebugShapeNearCollision.setFillColor(Color::Green);
		DebugShapeNearCollision.setOutlineThickness(1);
		DebugShapeNearCollision.setOutlineColor(Color(0, 0, 0, 255));
		DebugShapeNearCollision.setSize(Vector2f(3, 3));
	}

	for (unsigned int k = 0; k < NavigationMesh.size(); k++)
	{
		for (unsigned int j = 0; j < NavigationMesh[k].size(); j++)
		{	
			if (k == 16 && j == 8)
				cout << "" << endl;

			if(NavigationMesh[k][j]->GetCollision())
				DebugShapeCollision.setPosition(NavigationMesh[k][j]->Position);
			else if(NavigationMesh[k][j]->GetIsNearCollision())
				DebugShapeNearCollision.setPosition(NavigationMesh[k][j]->Position);
			else
				DebugShapeNonCollision.setPosition(NavigationMesh[k][j]->Position);

			Window->draw(DebugShapeNearCollision);
			Window->draw(DebugShapeNonCollision);
			Window->draw(DebugShapeCollision);
		}
	}
#endif
}