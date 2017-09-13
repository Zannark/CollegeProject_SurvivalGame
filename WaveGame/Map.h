#pragma once

#include <memory>
#include <vector>
#include "Prop.h"
#include "TextureCache.h"

using namespace std;

/// <summary>
/// Defines the world which the player can move around in and interact with.
/// </summary>
class Map
{
public:
	Map();
	Map(Vector2f Dimensions, string BackgroundID);
	~Map();

	void AddProp(shared_ptr<Prop> Prop);
	void Draw(RenderWindow *Window);
private:
	vector<shared_ptr<Prop>> MapProps;
	Vector2f MapDimensions;
	SmartTexture Background;
};

