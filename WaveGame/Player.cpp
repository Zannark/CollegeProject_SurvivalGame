#include "Player.h"

Engine::Gameplay::Player::Player()
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Tarn.png"));
	this->MovementSpeed = 150.0f;

	this->Texture->SetOrigin(Vector2f(this->Texture->GetSFMLTexture().getSize().x / 2, this->Texture->GetSFMLTexture().getSize().y / 2));
}

Engine::Gameplay::Player::~Player()
{
}

void Engine::Gameplay::Player::Update(shared_ptr<RenderWindow> Window, float dt)
{
	this->HandleMovement(dt);
	this->HandleRotation(Window, dt);
}

void Engine::Gameplay::Player::HandleMovement(float dt)
{
	Vector2f Offset = Vector2f(0, 0);

	if (Keyboard::isKeyPressed(Keyboard::Key::W))
		Offset.y -= this->MovementSpeed * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::S))
		Offset.y += this->MovementSpeed * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		Offset.x -= this->MovementSpeed * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		Offset.x += this->MovementSpeed * dt;

	this->Texture->Move(Offset);
}

void Engine::Gameplay::Player::HandleRotation(shared_ptr<RenderWindow> Window, float dt)
{
	this->Angle = atan2(Mouse::getPosition(*Window).y - this->Texture->GetSFMLSprite()->getPosition().y,
						Mouse::getPosition(*Window).x - this->Texture->GetSFMLSprite()->getPosition().x);

	this->Angle *= (180 / PI);

	if (Angle < 0)
		Angle += 360;

	this->Texture->SetRotation(Angle + 90);
}
