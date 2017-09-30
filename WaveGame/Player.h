#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>

#include "Common.h"
#include "SmartTexture.h"
#include "TextureCache.h"
#include "VectorMaths.h"
//#include "Character.h"
#include "SFML_Collision.h"
#include "Map.h"

using namespace sf;

class Character;

class Player : public Character
{
public:
	Player(RenderWindow *Window, string PlayerTexture = "DefaultPlayer", float PlayerSpeed = 150.0f);
	~Player();

	void Update(RenderWindow *Window, float dt);
	
private:
	View Camera;
	Vector2f Offset;

	float PlayerSpeed;
	float Angle;
	float StrafeSpeed;

	void HandleMovement(RenderWindow* Window, float dt);
	void HandleRotation(RenderWindow * Window);
	void HandleCamera(RenderWindow* Window, float dt);
};

