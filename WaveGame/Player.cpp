#include "Player.h"

Engine::GamePlay::Player::Player()
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Player.png"));
	this->MovementSpeed = 150.0f;

	this->Texture->SetOrigin(Vector2f((float)(this->Texture->GetSFMLTexture().getSize().x / 2), (float)(this->Texture->GetSFMLTexture().getSize().y / 2)));
	this->Texture->SetPosition(Vector2f(400, 400));

	this->Directions["Up"] = Vector2f(0, -1);
	this->Directions["Down"] = Vector2f(0, 1);
	this->Directions["Left"] = Vector2f(-1, 0);
	this->Directions["Right"] = Vector2f(1, 0);
	this->Directions["Still"] = Vector2f(0, 0);
}

Engine::GamePlay::Player::~Player()
{
}

void Engine::GamePlay::Player::Update(shared_ptr<RenderWindow> Window, Map M, float dt)
{	
	this->HandleMovement(M, dt);
	this->HandleRotation(Window, dt);
}

void Engine::GamePlay::Player::HandleMovement(Map M, float dt)
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

void Engine::GamePlay::Player::HandleRotation(shared_ptr<RenderWindow> Window, float dt)
{
	this->Angle = atan2(Mouse::getPosition(*Window).y - this->Texture->GetSFMLSprite()->getPosition().y,
						Mouse::getPosition(*Window).x - this->Texture->GetSFMLSprite()->getPosition().x);

	this->Angle *= (float)(180 / PI);

	if (Angle < 0)
		Angle += 360;

	this->Texture->SetRotation(Angle + 90);
}

bool Engine::GamePlay::Player::CheckCollision(Map M)
{
	for (auto Prop : M.GetProps())
		if (Collision::BoundingBoxTest(*this->Texture->GetSFMLSprite(), *Prop->GetSFMLSprite()))
			return true;
	return false;
}		
