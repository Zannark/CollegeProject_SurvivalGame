#pragma once

#include <memory>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include <iostream>
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
	};
}