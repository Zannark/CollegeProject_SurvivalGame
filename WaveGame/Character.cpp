#include "Character.h"

Character::Character(RenderWindow *Window, string PlayerTexture, float PlayerSpeed)
{
	this->PlayerTexture = TextureCache::GetTexure(PlayerTexture);
	this->PlayerSpeed = PlayerSpeed;
	this->Camera = View(this->PlayerTexture.GetPosition(), Vector2f(Window->getSize().x, Window->getSize().y));
	Window->setView(this->Camera);
}

Character::~Character()
{
}

void Character::Update(RenderWindow* Window, float dt)
{	
	this->HandleMovement(Window, dt);
	this->HandleCamera(Window, dt);
}

void Character::Draw(RenderWindow* Window)
{
	this->PlayerTexture.Draw(Window);
}

void Character::HandleMovement(RenderWindow* Window, float dt)
{
	this->Offset = Vector2f();
	
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

void Character::HandleCamera(RenderWindow* Window, float dt)
{
	this->Camera.move(this->Offset);
	Window->setView(this->Camera);
}
