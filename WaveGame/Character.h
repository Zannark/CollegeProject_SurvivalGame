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
	Character();
	~Character();

	void Draw(RenderWindow *Window);
	virtual void Update(RenderWindow *Window, float dt);
	
	SmartTexture GetTexture() const;
	void SetCanMove(bool CanMove);

protected:
	SmartTexture CharacterTexture;
	float HalfWidth;
	float HalfHeight;
	bool CanMoveInDirection;
	Vector2f Direction;
	///To keep track of the last direction where the player couldn't go in that direction.
	Vector2f LastDirectionCouldntMove;
};

