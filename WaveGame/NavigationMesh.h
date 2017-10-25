#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include "Common.h"
#include "Map.h"

using namespace sf;
using namespace std;

namespace Engine::Core
{
	class NavigationNode
	{
	public:
		NavigationNode(Vector2f Location);

		RectangleShape Shape;
		Vector2f Point;
	};

	class NavigationMesh
	{
	public:
		NavigationMesh(shared_ptr<RenderWindow> Window, Map M);
		~NavigationMesh();

	private:
		vector<NavigationNode> NavNodes;
		mutex LoadingMuxtex;
		thread LoadingThread;

		void CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Map M);
	};
}