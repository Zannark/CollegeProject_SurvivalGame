#include "Player.h"

Player::Player(RenderWindow *Window, string CharacterTexture, float PlayerSpeed)
{
	this->CharacterTexture = TextureCache::GetTexure(CharacterTexture);

	this->PlayerSpeed = PlayerSpeed;
	this->StrafeSpeed = 100.0f;
	this->HalfWidth = (float)(this->CharacterTexture.GetDimensions().x / 2);
	this->HalfHeight = (float)(this->CharacterTexture.GetDimensions().y / 2);
	this->CharacterTexture.SmartSprite.setOrigin(this->HalfWidth, this->HalfHeight);
	
	this->Camera = View(this->CharacterTexture.GetPosition(), Vector2f((float)Window->getSize().x, (float)Window->getSize().y));
	Window->setView(this->Camera);
}

Player::~Player()
{
}

/// <summary>
/// Updates the players game logic. This includes health, movement, etc...
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
/// <param name = "dt">Delta Time</param>
void Player::Update(RenderWindow* Window, float dt)
{	
	this->HandleRotation(Window);
	this->HandleMovement(Window, dt);
	this->HandleCamera(Window, dt);
}


/// <summary>
/// Handles all the logic for moving the player between two points.
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
/// <param name = "dt">Delta Time</param>
void Player::HandleMovement(RenderWindow* Window, float dt)
{
	this->Offset = Vector2f();

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && this->CanMoveInDirection)
		Offset.y -= this->PlayerSpeed * dt;
	else if(Keyboard::isKeyPressed(Keyboard::Key::W) && !this->CanMoveInDirection)
		Offset.y += (this->PlayerSpeed * dt) + 10;

	if (Keyboard::isKeyPressed(Keyboard::Key::S) && this->CanMoveInDirection)
		Offset.y += this->PlayerSpeed * dt;
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) && !this->CanMoveInDirection)
		Offset.y -= (this->PlayerSpeed * dt) + 10;
		
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && this->CanMoveInDirection)
		Offset.x -= this->PlayerSpeed * dt;
	else if (Keyboard::isKeyPressed(Keyboard::Key::A) && !this->CanMoveInDirection)
		Offset.x += (this->PlayerSpeed * dt) + 10;
	
	if (Keyboard::isKeyPressed(Keyboard::Key::D) && this->CanMoveInDirection)
		Offset.x += this->PlayerSpeed * dt;
	else if (Keyboard::isKeyPressed(Keyboard::Key::D) && !this->CanMoveInDirection)
		Offset.x -= (this->PlayerSpeed * dt) + 10;

	this->CharacterTexture.Move(Offset);
}

/// <summary>
/// Handles the logic for rotating the player.
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
void Player::HandleRotation(sf::RenderWindow * Window)
{
	Vector2i MousePosition = Mouse::getPosition(*Window);

	this->Angle = (float)atan2(Window->getPosition().y - MousePosition.y, Window->getPosition().x - MousePosition.x);
	this->Angle *= (float)(180 / PI);

	if (this->Angle < 360)
		this->Angle += 360;

	this->CharacterTexture.SmartSprite.setRotation(this->Angle - 90);
}

/// <summary>
/// Moves the camera.
/// </summary>
/// <param name = "Window">A pointer to the render target.</param>
/// <param name = "dt">Delta Time</param>
void Player::HandleCamera(RenderWindow* Window, float dt)
{
	this->Camera.move(this->Offset);
	Window->setView(this->Camera);
}
