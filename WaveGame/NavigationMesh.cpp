#include "NavigationMesh.h"

Engine::Core::NavigationNode::NavigationNode(Vector2f Location)
{
	this->Point = Location;
	
	this->Shape = RectangleShape(Vector2f(1, 1));
	this->Shape.setFillColor(Color::Red);
	this->Shape.setOutlineColor(Color::Transparent);
	this->Shape.setOutlineThickness(0);
}

Engine::Core::NavigationMesh::NavigationMesh(shared_ptr<RenderWindow> Window, Map M)
{
	this->LoadingThread = thread(&NavigationMesh::CreateNavigationMesh, this, Window, M);
	this->LoadingThread.detach();
}

void Engine::Core::NavigationMesh::CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Map M)
{
	lock_guard<mutex> Guard(this->LoadingMuxtex);

	Clock C;
	C.restart();

	auto Props = M.GetProps();

	for (int x = 0; x < (int)Window->getSize().x; x += 5)
	{
		for (int y = 0; y < (int)Window->getSize().y; y += 5)
		{
			for (auto P : Props)
			{
				///Used to make sure theres no props in this location.
				FloatRect Tester = FloatRect(x, y, 1, 1);
				if (!P->GetSFMLSprite()->getGlobalBounds().intersects(Tester))
					this->NavNodes.push_back(NavigationNode(Vector2f(x, y)));
			}
		}
	}

	cout << "Took " << C.getElapsedTime().asSeconds() << " seconds to create the Navigation Mesh" << endl;
}

Engine::Core::NavigationMesh::~NavigationMesh()
{

}