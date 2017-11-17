#include "NavigationMesh.h"

Engine::Core::NavigationNode::NavigationNode(Vector2f Location, Player P)
{
	this->Point = Location;

	this->Shape = make_shared<RectangleShape>(Vector2f(1, 1));
	this->Shape->setFillColor(Color(0, 75, 168));
	this->Shape->setOutlineColor(Color::Black);
	this->Shape->setOutlineThickness(1);
	this->Shape->setPosition(Location);
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
	this->IntervalCounter = 0;
}

void Engine::Core::NavigationMesh::CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Player P, Map M)
{
	lock_guard<mutex> Guard(this->LoadingMuxtex);

	auto Props = M.GetProps();
	
	for (float x = 0; x < (float)Window->getSize().x; x += NODE_DISTANCE)
	{
		for (float y = 0; y < (float)Window->getSize().y; y += NODE_DISTANCE)
		{
			///Used to make sure theres no props in this location.
			FloatRect Tester = FloatRect(x, y, 1.0f, 1.0f);
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

			if (!DoesCollision)
				this->NavNodes.push_back(NavigationNode(Vector2f(x, y), P));
		}	
	}
}

Engine::Core::NavigationMesh::~NavigationMesh()
{

}

void Engine::Core::NavigationMesh::Update(Player P, float dt)
{
	///Why is this a lambda? Only the gods know the reasoning.
	auto UpdateHandler = [this, P]() -> void
	{
		if (this->CurrentNodePosition >= this->NavNodes.size())
			this->CurrentNodePosition = 0;

		///This feels a bit cheatyyyy...?
		for (int Counter = 0; this->CurrentNodePosition < this->NavNodes.size(); this->CurrentNodePosition++)
		{
			if (Counter <= 100)
			{
				this->NavNodes[this->CurrentNodePosition].CalculateDistance(P);
				Counter += 1;
			}
			else
				break;
		}
	};

	this->IntervalCounter += 1;

	if (this->IntervalCounter >= INTERVAL_LIMIT)
	{
		this->IntervalCounter = 0;
		UpdateHandler();
	}
}

void Engine::Core::NavigationMesh::DebugDraw(shared_ptr<RenderWindow> Window)
{
	if (this->LoadingMuxtex.try_lock())
	{
		for (size_t i = 0; i < this->NavNodes.size(); i++)
			this->NavNodes[i].DebugDraw(Window);
		this->LoadingMuxtex.unlock();
	}
}
