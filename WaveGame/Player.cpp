#include "Player.h"
#include "EnemyManager.h"
#include "PowerUpBase.h"
#include "SpeedPowerUp.h"

///<summary>
///Constructs the player object.
///Loads the Animators for the player, player weapon, and the health bar icon from the cache.
///Sets the player at a random location.
///Loads the font for the powerup name in the UI.
///</summary>
Engine::GamePlay::Player::Player(RenderWindow* Wnd, Map M)
{
	this->CharacterAnimator = make_shared<Animator>(AnimationCache::Cache("Assets/Player.png"));
	this->PlayerWeapon = make_shared<Animator>(AnimationCache::Cache("Assets/PlayerWeapon.png"));
	this->HealthBarIcon = make_shared<Animator>(AnimationCache::Cache("Assets/HealthBarIcon.png"));
	this->MovementSpeed = 150.0f;
	this->MovementSpeedModifer = 1.f;
	this->AttackDamageModifier = 1;
	this->Health = PLAYER_MAX_HEALTH;
	this->OldHealth = PLAYER_MAX_HEALTH;

	this->CharacterAnimator->SetOrigin(Vector2f((float)(this->CharacterAnimator->GetSize().x / 2), (float)(this->CharacterAnimator->GetSize().y / 2)));
	
	GenerateRandomPlayerPosition(Wnd, M);

	this->PlayerWeapon->SetOrigin(Vector2f(this->PlayerWeapon->GetSize().x / 2, this->PlayerWeapon->GetSize().y - 4));

	this->HighHealthColour = Color(0, 255, 0);
	this->MediumHealthColour = Color(255, 219, 64); 
	this->LowHealthColour = Color(255, 0, 0);

	this->HealthBarIcon->SetPosition(Vector2f(5, 10));

	this->HealthBarOutLine = RectangleShape(Vector2f(200, 15));
	this->HealthBarOutLine.setFillColor(Color::Transparent);
	this->HealthBarOutLine.setOutlineColor(Color::Black);
	this->HealthBarOutLine.setOutlineThickness(4);
	this->HealthBarOutLine.setPosition(Vector2f(this->HealthBarIcon->GetSize().x + this->HealthBarOutLine.getOutlineThickness() + 10, (this->HealthBarIcon->GetSize().y / 2) + this->HealthBarOutLine.getOutlineThickness()));

	this->HealthBar = RectangleShape(Vector2f(200, 15));
	this->HealthBar.setFillColor(this->HighHealthColour);
	this->HealthBar.setOutlineColor(Color::Transparent);
	this->HealthBar.setOutlineThickness(0);
	this->HealthBar.setPosition(Vector2f(this->HealthBarIcon->GetSize().x + this->HealthBarOutLine.getOutlineThickness() + 10, (this->HealthBarIcon->GetSize().y / 2) + this->HealthBarOutLine.getOutlineThickness()));
	
	this->IsAlive = true;
	this->AttackTimer = PLAYER_ATTACK_INTERVAL;

	this->PowerUp = nullptr;

	this->PowerUpFont.loadFromFile("Assets/Heavy_Data.ttf");
	this->PowerUpText.setFont(this->PowerUpFont);
	this->PowerUpText.setFillColor(Color::Black);
	this->PowerUpText.setPosition(Vector2f(300, 12));
}

///<summary>
///Generates a random position on the screen and places the player there.
///Doesn't place a player in any props.
///</summary>
///<param name = "Wnd">The window which is being rendered to.</param>
///<param name = "M">The map which is being used.</param>
void Engine::GamePlay::Player::GenerateRandomPlayerPosition(RenderWindow* Wnd, Map &M)
{
	float X = 0;
	float Y = 0;
	bool HasCollisionOccured = false;

	while (true)
	{
		X = (float)(rand() % (int)(((Wnd->getSize().x - this->CharacterAnimator->GetSize().x) -
			(this->CharacterAnimator->GetSize().x - this->CharacterAnimator->GetSFMLSprite()->getOrigin().x) + 1) +
			(this->CharacterAnimator->GetSize().x - this->CharacterAnimator->GetSFMLSprite()->getOrigin().x)));

		Y = (float)(rand() % (int)(((Wnd->getSize().y - this->CharacterAnimator->GetSize().y) -
			(this->CharacterAnimator->GetSize().y - this->CharacterAnimator->GetSFMLSprite()->getOrigin().y) + 1) +
			(this->CharacterAnimator->GetSize().y - this->CharacterAnimator->GetSFMLSprite()->getOrigin().y)));

		for (Prop P : M.GetProps())
		{
			FloatRect PropBoundingBox;
			FloatRect CollisionTesterRect;

			CollisionTesterRect = FloatRect(X, Y, this->CharacterAnimator->GetSize().x, this->CharacterAnimator->GetSize().y);
			PropBoundingBox = get<0>(P)->GetSFMLSprite()->getGlobalBounds();

			if (CollisionTesterRect.intersects(PropBoundingBox))
				HasCollisionOccured = true;
		}

		if (HasCollisionOccured)
			HasCollisionOccured = false;
		else
			break;
	}

	this->CharacterAnimator->SetPosition(Vector2f(X, Y));
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
		this->UpdatePowerUp();
		this->PlayerWeapon->SetPosition(this->GetPosition());
		this->PlayerWeapon->SetRotation(this->Angle + 90);
		this->HandleAttack(M, dt);
		this->UpdateUI();
		this->UpdateHealthBar();
		this->HandleCollision(M, 0.1f);
	}
}

///<summary>
///Handles the powerup useage and lifetime.
///</summary>
void Engine::GamePlay::Player::UpdatePowerUp(void)
{
	if (this->PowerUp)
	{
		if (Keyboard::isKeyPressed(Keyboard::Key::E) && !((PowerUpBase*)this->PowerUp)->GetNeedsToBeDestroyed())
			((PowerUpBase*)this->PowerUp)->OnUse(this);

		if (((PowerUpBase*)this->PowerUp)->GetNeedsToBeDestroyed())
		{
			((PowerUpBase*)this->PowerUp)->OnUseEnd(this);
			this->PowerUp = nullptr;
			this->PowerUpText.setString("");
		}
	}
}

///<summary>
///Handles the left mouse button being pressed, and the attack call.
///Updates the attack timer.
///</summary>
///<param name = "dt">Delta time</param>
void Engine::GamePlay::Player::HandleAttack(Map M, float dt)
{
	if (Mouse::isButtonPressed(Mouse::Button::Left) && this->AttackTimer >= PLAYER_ATTACK_INTERVAL)
		this->Attack(M);
	this->AttackTimer += dt;
}

///<summary>
///Checks the players health and changes the colour of the health bar depending on their health.
///</summary>
void Engine::GamePlay::Player::UpdateHealthBar(void)
{
	if (this->Health >= PLAYER_HIGH_HEALTH_THRESHOLD && this->HealthBar.getFillColor() != this->HighHealthColour)
		this->HealthBar.setFillColor(this->HighHealthColour);
	else if (this->Health >= PLAYER_MEDIUM_HEALTH_THRESHOLD && this->Health < PLAYER_HIGH_HEALTH_THRESHOLD && this->HealthBar.getFillColor() != this->MediumHealthColour)
		this->HealthBar.setFillColor(this->MediumHealthColour);
	else if (this->HealthBar.getFillColor() != this->LowHealthColour && this->Health < PLAYER_MEDIUM_HEALTH_THRESHOLD)
		this->HealthBar.setFillColor(this->LowHealthColour);
}

///<summary>
///Gets the enemies which in range of the player and then deals a random amount of damage, between 0 and PLAYER_MAX_ATTACK_DAMAGE.
///</summary>
void Engine::GamePlay::Player::Attack(Map M)
{
	vector<Enemy*> Enemies = ((EnemyManager*)this->Manager)->GetEnemiesInRange();
	vector<Prop> Props = M.GetProps();

	for (Enemy* En : Enemies)
	{
		Prop CollisionProp = make_tuple<shared_ptr<Animator>, bool>(nullptr, false);

		for (Prop P : Props)
		{
			if (Collision::PixelPerfectTest(*get<0>(P)->GetSFMLSprite(), *this->PlayerWeapon->GetSFMLSprite()))
			{
				CollisionProp = P;
				break;
			}
		}

		if (!get<0>(CollisionProp))
		{
			int AttackDamage = rand() % (PLAYER_MAX_ATTACK_DAMAGE * this->AttackDamageModifier);
			En->TakeDamage(AttackDamage);
		}
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
	const float HalfPlayerSize = (this->CharacterAnimator->GetSize().y / 2);
	const PlayerCollisionResult CollisionResult = this->CheckCollision(M);

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && this->GetPosition().y - HalfPlayerSize > 0)
		Offset.y -= (this->MovementSpeed * this->MovementSpeedModifer) * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::S) && this->GetPosition().y + HalfPlayerSize < Window->getSize().y)
		Offset.y += (this->MovementSpeed * this->MovementSpeedModifer) * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::A) && this->GetPosition().x - HalfPlayerSize > 0)
		Offset.x -= (this->MovementSpeed * this->MovementSpeedModifer) * dt;

	if (Keyboard::isKeyPressed(Keyboard::Key::D) && this->GetPosition().x + HalfPlayerSize < Window->getSize().x)
		Offset.x += (this->MovementSpeed * this->MovementSpeedModifer) * dt;

	this->CharacterAnimator->Move(Offset);
}

///<summary>
///Handles the direction which the player is facing.
///</summary>
///<param name = "Window">A pointer to the RenderWindow which is being used.</param>
///<param name = "dt">Delta time, the time the last frame took.</param>
void Engine::GamePlay::Player::HandleRotation(RenderWindow* Window, float dt)
{
	this->Angle = atan2(Mouse::getPosition(*Window).y - this->CharacterAnimator->GetPosition().y,
						Mouse::getPosition(*Window).x - this->CharacterAnimator->GetPosition().x);

	this->Angle *= (float)(180 / PI);

	if (Angle < 0)
		Angle += 360;

	this->CharacterAnimator->SetRotation(Angle + 90);
}

///<summary>
///Stops the player from being able to move into props which have collision turned on.
///Pushes them out of the colliding prop.
///</summary>
///<param name = "M">A copy of the map for collision checking.</param>
///<param name = "MovementOffset">The amount to push the player back by.</param>
void Engine::GamePlay::Player::HandleCollision(Map M, float MovementOffset)
{
	PlayerCollisionResult Result = this->CheckCollision(M);

	///There has been no collision, no need to do anything else.
	if (!get<0>(Result))
		return;

	const float CollisionBuffer = 3.5f;

	shared_ptr<Animator> Prop = get<1>(Result);
	Vector2f PropCentre = Prop->GetSize();
	Vector2f PlayerCentre = this->GetSize();

	///Distance between the centres of each point.
	Vector2f Delta(Prop->GetPosition().x - this->GetPosition().x, Prop->GetPosition().y - this->GetPosition().y);
	Vector2f Intersection;
	Intersection.x = abs(Delta.x) - (PropCentre.x + PlayerCentre.x);
	Intersection.y = abs(Delta.y) - (PropCentre.y + PlayerCentre.y);

	if (Intersection.x < 0.0f && Intersection.y < 0.0f)
	{
		MovementOffset = min(max(MovementOffset, 0.f), 1.f);
		
		if (Intersection.x > Intersection.y)
		{
			///Move on the x axis, posative direction. 
			if (Delta.x > 0)
				this->CharacterAnimator->Move(Vector2f(Intersection.x * (1 - MovementOffset) + PlayerCentre.x - CollisionBuffer, 0));
			///Move on the x axis, negative direction.
			else
				this->CharacterAnimator->Move(Vector2f(-Intersection.x * (1 - MovementOffset) - PlayerCentre.x + CollisionBuffer, 0));
		}
		else
		{
			///Move on the y axis, posative direction. 
			if (Delta.y > 0) 
				this->CharacterAnimator->Move(Vector2f(0, Intersection.y * (1 - MovementOffset) + PlayerCentre.y - CollisionBuffer));
			///Move on the y axis, negative direction.
			else
				this->CharacterAnimator->Move(Vector2f(0, -Intersection.y * (1 - MovementOffset) - PlayerCentre.y + CollisionBuffer));
		}
	}
}

///<summary>
///Checks if the player is colliding with a prop on screen.
///</summary>
///<param name = "M">A copy of the Map for the player for movement.</param>
///<returns>True if there is collision, false otherwise.</returns>
PlayerCollisionResult Engine::GamePlay::Player::CheckCollision(Map M)
{
	for (auto Prop : M.GetProps())
		if (get<1>(Prop) && Collision::PixelPerfectTest(*this->CharacterAnimator->GetSFMLSprite(), *get<0>(Prop)->GetSFMLSprite()))
			return PlayerCollisionResult(true, get<0>(Prop));
	return PlayerCollisionResult(false, nullptr);
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
	this->HealthBarIcon->Draw(Window);
	Window->draw(this->HealthBarOutLine);
	Window->draw(this->HealthBar);
	Window->draw(this->PowerUpText);
}

///<summary>
///Renders the weapon to the screen.
///</summary>
///<param name = "Window">A pointer to the RenderWindow to draw to.</param>
void Engine::GamePlay::Player::DrawWeapon(RenderWindow * Window)
{
	this->PlayerWeapon->Draw(Window);
}

///<summary>
///Sets the Movement Speec modifier.
///</summary>
///<param name = "Modifier">The modifier to apply to the movement speed.</param>
void Engine::GamePlay::Player::SetSpeedModifier(float Modifier)
{
	this->MovementSpeedModifer = Modifier;
}

///<summary>
///Sets the amount that the damage multiplier is.
///</summary>
///<param name = "Modifier">The multiplier amount.</param>
void Engine::GamePlay::Player::SetDamageModifier(int Modifier)
{
	this->AttackDamageModifier = Modifier;
}

///<summary>
///If the current power up is a nullptr, then it'll be assigned.
///Otherwise the passed power up will be flaged for destruction.
///</summary>
///<param name = "Power">The new power up which was walked over.</param>
void Engine::GamePlay::Player::SetPowerUp(void* Power)
{
	if (!this->PowerUp)
	{
		this->PowerUp = Power;
		this->SetPowerUpText(((PowerUpBase*)Power)->GetPowerUpName());
	}
	else
		((PowerUpBase*)Power)->SetNeedsToBeDestroyed();
}

///<summary>
///Sets the power up text.
///</summary>
///<param name = "PowerUpMark">The power up name, to be displayed on the UI.</param>
void Engine::GamePlay::Player::SetPowerUpText(string PowerUpName)
{
	if(this->PowerUp)
	{
		this->PowerUpName = PowerUpName;
		this->PowerUpText.setString(this->PowerUpName);
	}
}

///<summary>
///Gets a pointer to the player weapon.
///</summary>
///<returns>The pointer to the player weapon.</returns>
shared_ptr<Animator> Engine::GamePlay::Player::GetPlayerWeapon(void) const
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
