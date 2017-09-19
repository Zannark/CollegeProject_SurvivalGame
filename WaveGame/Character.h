#pragma once

#include <SFML\Graphics.hpp>
#include <math.h>

#include "Common.h"
#include "SmartTexture.h"
#include "TextureCache.h"
#include "VectorMaths.h"

using namespace sf;

class Character
{
public:
	Character(RenderWindow *Window, string PlayerTexture = "DefaultPlayer", float PlayerSpeed = 150.0f);
	~Character();

	void Update(RenderWindow *Window, float dt);
	void Draw(RenderWindow *Window);

private:
	SmartTexture PlayerTexture;
	View Camera;
	Vector2f Offset;

	float PlayerSpeed;
	float HalfWidth;
	float HalfHeight;
	float Angle;

	void HandleMovement(RenderWindow* Window, float dt);
	void HandleRotation(RenderWindow * Window);
	void HandleCamera(RenderWindow* Window, float dt);
};

