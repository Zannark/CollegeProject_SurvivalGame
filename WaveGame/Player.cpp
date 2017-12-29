#include "Player.h"
#include "EnemyManager.h"

Engine::GamePlay::Player::Player()
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Player.png"));
	this->MovementSpeed = 150.0f;
	this->Health = PLAYER_MAX_HEALTH;

	this->Texture->SetOrigin(Vector2f((float)(this->Texture->GetSFMLTexture()->getSize().x / 2), (float)(this->Texture->GetSFMLTexture()->getSize().y / 2)));
	this->Texture->SetPosition(Vector2f(400, 400));

	this->PlayerWeapon = RectangleShape(Vector2f(15, 55));
	this->PlayerWeapon.setFillColor(Color::Green);
	this->PlayerWeapon.setOutlineColor(Color::Black);
	this->PlayerWeapon.setOutlineThickness(1);

	this->HealthBar = RectangleShape(Vector2f(200, 30));
	this->HealthBar.setFillColor(Color(188, 28, 28));
	this->HealthBar.setOutlineColor(Color::Transparent);
	this->HealthBar.setOutlineThickness(1);
	this->HealthBar.setPosition(Vector2f(10, 10));

	this->HealthBarOutLine = RectangleShape(Vector2f(200, 30));
	this->HealthBarOutLine.setFillColor(Color::Transparent);
	this->HealthBarOutLine.setOutlineColor(Color::Black);
	this->HealthBarOutLine.setOutlineThickness(5);
	this->HealthBarOutLine.setPosition(Vector2f(10, 10));

	this->IsAlive = true;
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

		this->PlayerWeapon.setPosition(this->GetPosition() + Div(Vector2f(this->GetSize()), 2));

		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{
			this->Attack();
		}
	}
}

void Engine::GamePlay::Player::Attack(void)
{
	FloatRect WeaponBox = FloatRect(this->PlayerWeapon.getPosition().x, this->PlayerWeapon.getPosition().y, this->PlayerWeapon.getSize().x, this->PlayerWeapon.getSize().y);
	auto Enemies = ((EnemyManager*)this->Manager)->GetEnemiesInRange(WeaponBox);

	for(auto En : Enemies)
	{
		int AttackDamage = rand() % PLAYER_MAX_ATTACK_DAMAGE;

		En->TakeDamage(AttackDamage);
	}
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

void Engine::GamePlay::Player::SetEnemyManager(void* Manager)
{
	this->Manager = Manager;
}

void Engine::GamePlay::Player::DrawUI(RenderWindow * Window)
{
	Window->draw(this->HealthBarOutLine);
	Window->draw(this->HealthBar);
}

void Engine::GamePlay::Player::DrawWeapon(RenderWindow * Window)
{
	Window->draw(this->PlayerWeapon);
}

void Engine::GamePlay::Player::UpdateUI(void)
{
	cout << NormaliseToRange(0.1, 1, this->Health) << endl;
	this->HealthBar.setSize(Vector2f((((this->Health / PLAYER_MAX_HEALTH) * 100) * 10), this->HealthBar.getSize().y));
}
