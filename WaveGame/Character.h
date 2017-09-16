#pragma once

#include <SFML\Graphics.hpp>

#include "Common.h"
#include "SmartTexture.h"
#include "TextureCache.h"

using namespace sf;

class Character
{
public:
	Character(string PlayerTexture = "DefaultPlayer", float PlayerSpeed = 5.0f);
	~Character();

	void Update(RenderWindow *Window, float dt);
	void Draw(RenderWindow *Window);

private:
	SmartTexture PlayerTexture;
	float PlayerSpeed;
	
	void HandleMovement(RenderWindow* Window, float dt);
};

