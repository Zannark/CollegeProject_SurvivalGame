#include "NavigationMesh.h"

Engine::Core::NavigationNode::NavigationNode(Vector2f Location, Player P, bool IsUseable)
{
	this->Point = Location;
	this->IsUseable = IsUseable;

	if (IsUseable)
	{
		this->Shape = make_shared<RectangleShape>(Vector2f(1, 1));
		this->Shape->setFillColor(Color(0, 75, 168));
		this->Shape->setOutlineColor(Color::Black);
		this->Shape->setOutlineThickness(1);
		this->Shape->setPosition(Location);
	}
	else
	{
		this->Shape = make_shared<RectangleShape>(Vector2f(1, 1));
		this->Shape->setFillColor(Color(Color::Green));
		this->Shape->setOutlineColor(Color::Green);
		this->Shape->setOutlineThickness(1);
		this->Shape->setPosition(Location);
	}
}

bool Engine::Core::NavigationNode::operator==(const NavigationNode & Rhs)
{
	return (this->Point == Rhs.Point);
}

bool Engine::Core::NavigationNode::operator==(const Vector2f& Rhs)
{
	return (this->Point == Rhs);
}

void Engine::Core::NavigationNode::CalculateDistance(Player P)
{
	this->Estimate = EuclideanDistance(P.GetPosition(), this->Point);
}

void Engine::Core::NavigationNode::DebugDraw(shared_ptr<RenderWindow> Window)
{
	Window->draw(*this->Shape);
}

Engine::Core::NavigationMesh::NavigationMesh(shared_ptr<RenderWindow> Window, Player P, Map M)
{
	///Create a new thread so that it can run in the background and not cause the game to lock up.
	this->LoadingThread = thread(&NavigationMesh::CreateNavigationMesh, this, Window, P, M);
	this->LoadingThread.detach();

	this->CurrentNodePosition = 0;
	this->CurrentNodeRow = 0;
	this->IntervalCounter = 0;
}

///I DECREE YOU FUNCTION OF WORKING.
///IF ANY DARE PLACE THEIR HANDS UPON YOUR BAD CODE THEY SHALL FACE THE CHOPPING BLOCK <3
void Engine::Core::NavigationMesh::CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Player P, Map M)
{
	lock_guard<mutex> Guard(this->LoadingMuxtex);
	auto Props = M.GetProps();
	int Rows = 0;
	size_t x = 0;
	
	for (float i = 0; x < (float)Window->getSize().x; i++)
	{
		this->NavNodes.push_back(vector<NavigationNode>());
		size_t y = 0;

		for (float j = 0; y < (float)Window->getSize().y; j++)
		{
			///Used to make sure theres no props in this location.
			FloatRect Tester = FloatRect((float)x, (float)y, 1.0f, 1.0f);
			///Used for finding if the node is placed in a location where a prop is.
			bool DoesCollision = false;
			
			for (auto P : Props)
			{
				if (P->GetSFMLSprite()->getGlobalBounds().intersects(Tester))
				{
					DoesCollision = true;
					break;
				}
			} 

			this->NavNodes[(size_t)i].push_back(NavigationNode(Vector2f((float)x, (float)y), P, !DoesCollision));

			y += NODE_DISTANCE;
		}

		x += NODE_DISTANCE;
		Rows += 1;
	}

	this->NodeInformation["Row"] = Rows;
}

Engine::Core::NavigationMesh::~NavigationMesh()
{

}

void Engine::Core::NavigationMesh::Update(Player P, float dt)
{
	if (this->LoadingMuxtex.try_lock())
	{
		///Why is this a lambda? Only the gods know the reasoning.
		auto UpdateHandler = [this, P]() -> void
		{
			if (this->CurrentNodeRow >= this->NavNodes.size())
				this->CurrentNodeRow = 0;
			
			if (this->CurrentNodePosition >= this->NavNodes[this->CurrentNodeRow].size())
				this->CurrentNodePosition = 0;

			///This feels a bit cheatyyyy...?
			for (int x = 0; this->CurrentNodePosition < this->NavNodes[this->CurrentNodeRow].size(); x++)
			{
				for (int Counter = 0; this->CurrentNodePosition < this->NavNodes[this->CurrentNodeRow].size(); this->CurrentNodePosition++)
				{
					if (Counter <= UPDATE_LIMIT)
					{
						this->NavNodes[this->CurrentNodeRow][this->CurrentNodePosition].CalculateDistance(P);
						Counter += 1;
					}
					else
						break;
				}
			}

			this->CurrentNodeRow += 1;
		};

		this->IntervalCounter += 1;

		if (this->IntervalCounter >= INTERVAL_LIMIT)
		{
			this->IntervalCounter = 0;
			UpdateHandler();
		
			
		}
		
		this->LoadingMuxtex.unlock();
	}
}


void Engine::Core::NavigationMesh::DebugDraw(shared_ptr<RenderWindow> Window)
{
	if (this->LoadingMuxtex.try_lock())
	{
		for (size_t x = 0; x < this->NavNodes.size(); x++)
		{
			for (size_t y = 0; y < this->NavNodes[x].size(); y++)
			{
				this->NavNodes[x][y].DebugDraw(Window);
			}
		}
		
		this->LoadingMuxtex.unlock();
	}
}

NavigationNode Engine::Core::NavigationMesh::Get(Vector2i Position)
{
	return this->NavNodes[Position.x][Position.y];
}

Vector2i Engine::Core::NavigationMesh::GetCellFromPosition(Vector2f Position)
{
	return Vector2i((int)Position.x / NODE_DISTANCE, (int)Position.y / NODE_DISTANCE);
}

Vector2f Engine::Core::NavigationMesh::GetPositionFromCell(Vector2i Cell)
{
	return Vector2f(Cell.x * NODE_DISTANCE, Cell.y * NODE_DISTANCE);
}
