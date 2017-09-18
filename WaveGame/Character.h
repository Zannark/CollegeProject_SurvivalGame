#pragma once

#include <SFML\Graphics.hpp>

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

	void HandleMovement(RenderWindow* Window, float dt);
	void HandleCamera(RenderWindow* Window, float dt);
};

