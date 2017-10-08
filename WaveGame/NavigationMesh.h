#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include "Map.h"

using namespace std;
using namespace sf;

struct NavigationNode
{
	NavigationNode(float x, float y)
	{
		Position = Vector2f(x, y);
	}

	Vector2f Position;
};

class NavigationMesh
{
public:
	NavigationMesh(Map *Map);
	~NavigationMesh();
	
	void Draw(RenderWindow *Window);

private:
	vector<NavigationNode> Nodes;
	vector<RectangleShape> NodeDrawDebug;
};

