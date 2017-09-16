#include "Character.h"

Character::Character(string PlayerTexture, float PlayerSpeed)
{
	this->PlayerTexture = TextureCache::GetTexure(PlayerTexture);
	this->PlayerSpeed = PlayerSpeed;
}

Character::~Character()
{
}

void Character::Update(RenderWindow* Window, float dt)
{	
	this->HandleMovement(Window, dt);
}

void Character::Draw(RenderWindow* Window)
{
	this->PlayerTexture.Draw(Window);
}

void Character::HandleMovement(RenderWindow* Window, float dt)
{
	Vector2f Offset = Vector2f();
	
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
		Offset.y -= this->PlayerSpeed;

	if (Keyboard::isKeyPressed(Keyboard::Key::S))
		Offset.y += this->PlayerSpeed;

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		Offset.x -= this->PlayerSpeed;

	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		Offset.x += this->PlayerSpeed;

	Offset *= dt;
	this->PlayerTexture.Move(Offset);
}
