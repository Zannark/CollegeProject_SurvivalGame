#include "Player.h"

Engine::GamePlay::Player::Player()
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Player.png"));
	this->MovementSpeed = 150.0f;
	this->Health = 20;

	this->Texture->SetOrigin(Vector2f((float)(this->Texture->GetSFMLTexture()->getSize().x / 2), (float)(this->Texture->GetSFMLTexture()->getSize().y / 2)));
	this->Texture->SetPosition(Vector2f(400, 400));

	this->PlayerWeapon = RectangleShape(Vector2f(8, 15));
	this->PlayerWeapon.setFillColor(Color::Green);
	this->PlayerWeapon.setOutlineColor(Color::Black);
	this->PlayerWeapon.setOutlineThickness(1);
}

Engine::GamePlay::Player::~Player()
{
}

void Engine::GamePlay::Player::Update(RenderWindow* Window, Map M, float dt)
{	
	if (this->CheckHealth())
	{
		this->HandleMovement(Window, M, dt);
		this->HandleRotation(Window, dt);
	
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			//this->Attack();
		}
	}
}

void Engine::GamePlay::Player::Attack(void)
{
	FloatRect WeaponBox = FloatRect(this->PlayerWeapon.getPosition().x, this->PlayerWeapon.getPosition().y, this->PlayerWeapon.getSize().x, this->PlayerWeapon.getSize().y);
	auto Enemies = this->Manager->GetEnemiesInRange(WeaponBox);

	cout << Enemies.size() << endl;
}

void Engine::GamePlay::Player::HandleMovement(RenderWindow* Window, Map M, float dt)
{
	Vector2f Offset = Vector2f(0, 0);

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && this->GetPosition().y - (this->Texture->GetSFMLTexture()->getSize().y / 2) > 0)
		Offset.y -= this->MovementSpeed * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::S) && this->GetPosition().y + (this->Texture->GetSFMLTexture()->getSize().y / 2) < Window->getSize().y)
		Offset.y += this->MovementSpeed * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::A) && this->GetPosition().x - (this->Texture->GetSFMLTexture()->getSize().y / 2) > 0)
		Offset.x -= this->MovementSpeed * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::D) && this->GetPosition().x + (this->Texture->GetSFMLTexture()->getSize().y / 2) < Window->getSize().x)
		Offset.x += this->MovementSpeed * dt;

	this->Texture->Move(Offset);
}

void Engine::GamePlay::Player::HandleRotation(RenderWindow* Window, float dt)
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

void Engine::GamePlay::Player::TakeDamage(int Amount)
{
	cout << this->Health << endl;
	if (this->CheckHealth())
	{
		this->Health -= Amount;
	}
}

void Engine::GamePlay::Player::SetEnemyManager(EnemyManager * Manager)
{
	this->Manager = Manager;
}

bool Engine::GamePlay::Player::CheckHealth(void)
{
	if (this->Health <= 0)
	{
		///Death stuff here
		cout << "Died" << endl;
		return false;
	}
	return true;
}
