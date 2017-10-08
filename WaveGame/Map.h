#pragma once

#include <memory>
#include <vector>
#include "Prop.h"
#include "TextureCache.h"
#include "Character.h"
#include "SFML_Collision.h"

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
	void DrawBackground(RenderWindow *Window);
	void DrawProps(RenderWindow *Window);
	void Update(RenderWindow *Window, Character& P, float dt);
	vector<shared_ptr<Prop>> GetPropsWithTag(string Tag);
	vector<shared_ptr<Prop>> GetProps(void);
	SmartTexture GetBackground(void);
	
private:
	vector<shared_ptr<Prop>> MapProps;
	Vector2f MapDimensions;
	SmartTexture Background;

	void HandleCollision(RenderWindow *Window, Character& P, float dt);
};

