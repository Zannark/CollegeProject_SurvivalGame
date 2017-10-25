#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include "Common.h"
#include "Map.h"

using namespace sf;
using namespace std;

#define NODE_DISTANCE 15

namespace Engine::Core
{
	class NavigationNode
	{
	public:
		NavigationNode(Vector2f Location);

		bool operator==(const NavigationNode& Rhs);
		bool operator==(const Vector2f& Rhs);

		void DebugDraw(shared_ptr<RenderWindow> Window);

		shared_ptr<RectangleShape> Shape;
		Vector2f Point;
	};

	class NavigationMesh
	{
	public:
		NavigationMesh(shared_ptr<RenderWindow> Window, Map M);
		~NavigationMesh();

		void DebugDraw(shared_ptr<RenderWindow> Window);

	private:
		vector<NavigationNode> NavNodes;
		mutex LoadingMuxtex;
		thread LoadingThread;
		
		void CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Map M);
	};
}