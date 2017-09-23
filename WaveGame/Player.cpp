#include "Player.h"

Player::Player(RenderWindow *Window, string CharacterTexture, float PlayerSpeed)
{
	this->CharacterTexture = TextureCache::GetTexure(CharacterTexture);

	this->PlayerSpeed = PlayerSpeed;
	this->StrafeSpeed = 100.0f;
	this->HalfWidth = (this->CharacterTexture.GetDimensions().x / 2);
	this->HalfHeight = (this->CharacterTexture.GetDimensions().y / 2);
	this->CharacterTexture.SmartSprite.setOrigin(this->HalfWidth, this->HalfHeight);
	
	this->Camera = View(this->CharacterTexture.GetPosition(), Vector2f(Window->getSize().x, Window->getSize().y));
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
	this->Direction = Vector2f(cos(ToRadians(this->Angle)), sin(ToRadians(this->Angle)));
	
	if (Magnitude(Direction) > 0)
		Direction = Normalise(Direction);

	Vector2f Per = Perpendicular(Direction);

	if (Keyboard::isKeyPressed(Keyboard::Key::W) && this->LastDirectionCouldntMove != this->Direction)
	{
		Offset.x += this->PlayerSpeed * Direction.x * dt;
		Offset.y += this->PlayerSpeed * Direction.y * dt;
	}
	else if(Keyboard::isKeyPressed(Keyboard::Key::W) && this->LastDirectionCouldntMove == this->Direction && !this->CanMoveInDirection)
	{
		Offset.x -= this->PlayerSpeed * Direction.x * dt;
		Offset.y -= this->PlayerSpeed * Direction.y * dt;
	}
	
	if (Keyboard::isKeyPressed(Keyboard::Key::S) && this->LastDirectionCouldntMove != this->Direction)
	{
		Offset.x -= this->PlayerSpeed * Direction.x * dt;
		Offset.y -= this->PlayerSpeed * Direction.y * dt;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S) && this->LastDirectionCouldntMove == this->Direction && !this->CanMoveInDirection)
	{
		Offset.x += this->PlayerSpeed * Direction.x * dt;
		Offset.y += this->PlayerSpeed * Direction.y * dt;
	}

	/*if (Keyboard::isKeyPressed(Keyboard::Key::A))
		Offset.x -= Per.x * this->StrafeSpeed * dt;
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		Offset.x += Per.x * this->StrafeSpeed * dt;*/

	this->CharacterTexture.Move(Offset);
}

/// <summary>
/// Handles the logic for rotating the player.
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
void Player::HandleRotation(sf::RenderWindow * Window)
{
	Vector2i MousePosition = Mouse::getPosition(*Window);

	this->Angle = atan2(Window->getPosition().y - MousePosition.y, Window->getPosition().x - MousePosition.x);
	this->Angle *= (180 / PI);

	if (this->Angle < 360)
		this->Angle += 360;

	this->CharacterTexture.SmartSprite.setRotation(this->Angle + 90);
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
