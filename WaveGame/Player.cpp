#include "Player.h"
#include "EnemyManager.h"

Engine::GamePlay::Player::Player()
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/Player.png"));
	this->PlayerWeapon = make_shared<GameTexture>(TextureCache::Cache.Access("Assets/PlayerWeapon.png"));
	this->MovementSpeed = 150.0f;
	this->Health = PLAYER_MAX_HEALTH;
	this->OldHealth = PLAYER_MAX_HEALTH;

	this->Texture->SetOrigin(Vector2f((float)(this->Texture->GetSFMLTexture()->getSize().x / 2), (float)(this->Texture->GetSFMLTexture()->getSize().y / 2)));
	this->Texture->SetPosition(Vector2f(400, 400));

	this->PlayerWeapon->SetOrigin(Vector2f(this->PlayerWeapon->GetSize().x / 2, this->PlayerWeapon->GetSize().y - 4));
	//this->PlayerWeapon->GetSFMLTexture()->setSmooth(true);

	this->HealthBar = RectangleShape(Vector2f(200, 15));
	this->HealthBar.setFillColor(Color(188, 28, 28));
	this->HealthBar.setOutlineColor(Color::Transparent);
	this->HealthBar.setOutlineThickness(1);
	this->HealthBar.setPosition(Vector2f(10, 10));

	this->HealthBarOutLine = RectangleShape(Vector2f(200, 15));
	this->HealthBarOutLine.setFillColor(Color::Transparent);
	this->HealthBarOutLine.setOutlineColor(Color::Black);
	this->HealthBarOutLine.setOutlineThickness(4);
	this->HealthBarOutLine.setPosition(Vector2f(10, 10));

	this->IsAlive = true;
	this->AttackTimer = PLAYER_ATTACK_INTERVAL;
}

Engine::GamePlay::Player::~Player()
{
}

///<summary>
///Updates the player and its status once per frame.
///</summary>
///<param name = "Window">A pointer to the RenderWindow which is being used.</param>
///<param name = "M">A copy of the Map for the player for movement.</param>
///<param name = "dt">Delta time, the time the last frame took.</param>
void Engine::GamePlay::Player::Update(RenderWindow* Window, Map M, float dt)
{
	if (this->CheckHealth())
	{
		this->HandleMovement(Window, M, dt);
		this->HandleRotation(Window, dt);

		Vector2f WeaponPosition = this->GetPosition();
		this->PlayerWeapon->SetPosition(WeaponPosition);
		this->PlayerWeapon->SetRotation(this->Angle + 90);

		if (Mouse::isButtonPressed(Mouse::Button::Left) && this->AttackTimer >= PLAYER_ATTACK_INTERVAL)
			this->Attack();

		this->UpdateUI();
		this->AttackTimer += dt;
	}
}

///<summary>
///Gets the enemies which in range of the player and then deals a random amount of damage, between 0 and PLAYER_MAX_ATTACK_DAMAGE.
///</summary>
void Engine::GamePlay::Player::Attack(void)
{
	FloatRect WeaponBox = FloatRect(this->PlayerWeapon->GetPosition().x, this->PlayerWeapon->GetPosition().y, this->PlayerWeapon->GetSize().x, this->PlayerWeapon->GetSize().y);
	auto Enemies = ((EnemyManager*)this->Manager)->GetEnemiesInRange(WeaponBox);

	for(auto En : Enemies)
	{
		int AttackDamage = rand() % PLAYER_MAX_ATTACK_DAMAGE;

		En->TakeDamage(AttackDamage);
	}

	this->AttackTimer = 0;
}

///<summary>
///Moves the player in a given direcion.
///</summary>
///<param name = "Window">A pointer to the RenderWindow which is being used.</param>
///<param name = "M">A copy of the Map for the player for movement.</param>
///<param name = "dt">Delta time, the time the last frame took.</param>
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

///<summary>
///Handles the direction which the player is facing.
///</summary>
///<param name = "Window">A pointer to the RenderWindow which is being used.</param>
///<param name = "dt">Delta time, the time the last frame took.</param>
void Engine::GamePlay::Player::HandleRotation(RenderWindow* Window, float dt)
{
	this->Angle = atan2(Mouse::getPosition(*Window).y - this->Texture->GetSFMLSprite()->getPosition().y,
						Mouse::getPosition(*Window).x - this->Texture->GetSFMLSprite()->getPosition().x);

	this->Angle *= (float)(180 / PI);

	if (Angle < 0)
		Angle += 360;

	this->Texture->SetRotation(Angle + 90);
}

///<summary>
///Checks if the player is colliding with a prop on screen.
///</summary>
///<param name = "M">A copy of the Map for the player for movement.</param>
///<returns>True if there is collision, false otherwise.</returns>
bool Engine::GamePlay::Player::CheckCollision(Map M)
{
	for (auto Prop : M.GetProps())
		if (Collision::BoundingBoxTest(*this->Texture->GetSFMLSprite(), *Prop->GetSFMLSprite()))
			return true;
	return false;
}

///<summary>
///Sets the pointer to the Enemy manager.
///</summary>
///<param name = "Manager">The pointer to the manager.</param>
void Engine::GamePlay::Player::SetEnemyManager(void* Manager)
{
	this->Manager = Manager;
}

///<summary>
///Resets the health of the player to full.
///</summary>
void Engine::GamePlay::Player::SetFullHealth(void)
{
	this->Health = PLAYER_MAX_HEALTH;
	this->UpdateUI();
}

///<summary>
///Sets the health of the player to half of the difference between the current amount of health and PLAYER_MAX_HEALTH.
///</summary>
void Engine::GamePlay::Player::RegenHalfMissingHealth(void)
{
	this->Health += (abs(this->Health - PLAYER_MAX_HEALTH) / 2);
	this->UpdateUI();
}

///<summary>
///Renders the UI to the screen.
///</summary>
///<param name = "Window">A pointer to the RenderWindow to draw to.</param>
void Engine::GamePlay::Player::DrawUI(RenderWindow * Window)
{
	Window->draw(this->HealthBarOutLine);
	Window->draw(this->HealthBar);
}

///<summary>
///Renders the weapon to the screen.
///</summary>
///<param name = "Window">A pointer to the RenderWindow to draw to.</param>
void Engine::GamePlay::Player::DrawWeapon(RenderWindow * Window)
{
	this->PlayerWeapon->Draw(Window);
}

shared_ptr<GameTexture> Engine::GamePlay::Player::GetPlayerWeapon(void) const
{
	return this->PlayerWeapon;
}

///<summary>
///Update the on screen UI.
///</summary>
void Engine::GamePlay::Player::UpdateUI(void)
{
	this->HealthBar.setSize(Vector2f((float)this->Health, this->HealthBar.getSize().y));
}
