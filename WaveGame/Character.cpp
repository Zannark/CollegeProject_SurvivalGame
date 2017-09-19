#include "Character.h"

Character::Character(RenderWindow *Window, string PlayerTexture, float PlayerSpeed)
{
	this->PlayerTexture = TextureCache::GetTexure(PlayerTexture);

	this->PlayerSpeed = PlayerSpeed;
	this->HalfWidth = (this->PlayerTexture.GetDimensions().x / 2);
	this->HalfHeight = (this->PlayerTexture.GetDimensions().y / 2);
	this->PlayerTexture.SmartSprite.setOrigin(this->HalfWidth, this->HalfHeight);
	
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

	Vector2i MousePosition = Mouse::getPosition(*Window);
	float Angle = atan2(MousePosition.y - this->PlayerTexture.GetPosition().y, MousePosition.x - this->PlayerTexture.GetPosition().x);
	Angle *= (180 / 3.142);

	if (Angle < 360)
		Angle = 360 - (-Angle);

	this->PlayerTexture.SmartSprite.setRotation(Angle);
}

void Character::HandleCamera(RenderWindow* Window, float dt)
{
	this->Camera.move(this->Offset);
	Window->setView(this->Camera);
}
