#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
}

/// <summary>
/// Renders the character to the screen.
/// </summary>
/// <param name = "Window">The render target.</param>
void Character::Draw(RenderWindow* Window)
{
	this->CharacterTexture.Draw(Window);
}

void Character::Update(RenderWindow* Window, float dt)
{
}

SmartTexture Character::GetTexture() const
{
	return this->CharacterTexture;
}

void Character::SetCanMove(bool CanMove)
{
	this->CanMoveInDirection = CanMove;

	if (!this->CanMoveInDirection)
		this->LastDirectionCouldntMove = this->Direction;
}
