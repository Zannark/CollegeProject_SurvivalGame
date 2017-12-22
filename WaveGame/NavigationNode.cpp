#include "NavigationNode.h"

namespace
{
	vector<vector<shared_ptr<Engine::Core::NavigationNode>>> NavigationMesh;
}

void Engine::Core::CreateNavigationMesh(shared_ptr<RenderWindow> Window, Player P, Map M)
{
	///For ease
	const float Width = Window->getSize().x;
	const float Height = Window->getSize().y;
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

			Count += 1;
		}

		x += NAVIGATION_NODE_DISTANCE;
	}

	cout << Count << endl;
}

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

Engine::Core::NavigationNode::NavigationNode(Vector2f Position, shared_ptr<RenderWindow> Window, bool DoesCollision)
{
	this->Position = Position;
	this->Window = Window;
	this->DoesCollision = DoesCollision;
}

Engine::Core::NavigationNode::NavigationNode(float x, float y, shared_ptr<RenderWindow> Window, bool DoesCollision)
{
	this->Position = Vector2f(x, y);
	this->DoesCollision = DoesCollision;
	this->Window = Window;
}

float Engine::Core::NavigationNode::GoalDistanceEstimate(NavigationNode& GoalNode)
{
	return EuclideanDistance(GoalNode.Position, this->Position);
}

bool Engine::Core::NavigationNode::IsGoal(NavigationNode& GoalNode)
{
	return (this->Position == GoalNode.Position);
}

bool Engine::Core::NavigationNode::GetSuccessors(AStarSearch<NavigationNode>* AStarSearch, NavigationNode* ParentNode)
{
	auto AddSuccessor = [this, AStarSearch, ParentNode](Vector2f Position)
	{
		auto Node = GetNodeByPosition(Position);
		if (Node != nullptr && (!ParentNode || !Node->IsSameState(*ParentNode)))
			AStarSearch->AddSuccessor(*Node);
	};

	//Vector2f ParentPosition(-1, -1);
	//NavigationNode NewNode;
	
	//if (ParentNode)
		//ParentPosition = ParentNode->Position;

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

float Engine::Core::NavigationNode::GetCost(NavigationNode& Successor)
{
	return fabsf(EuclideanDistance(this->Position, Successor.Position));
}

bool Engine::Core::NavigationNode::IsSameState(NavigationNode& OtherNode)
{
	return (((int)floorf(this->Position.x) == (int)floorf(OtherNode.Position.x)) && ((int)floorf(this->Position.y) == (int)floorf(OtherNode.Position.y)));
}
