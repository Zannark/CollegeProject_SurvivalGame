#include "Character.h"

Character::Character(RenderWindow *Window, string PlayerTexture, float PlayerSpeed)
{
	this->PlayerTexture = TextureCache::GetTexure(PlayerTexture);

	this->PlayerSpeed = PlayerSpeed;
	this->StrafeSpeed = 100.0f;
	this->HalfWidth = (this->PlayerTexture.GetDimensions().x / 2);
	this->HalfHeight = (this->PlayerTexture.GetDimensions().y / 2);
	this->PlayerTexture.SmartSprite.setOrigin(this->HalfWidth, this->HalfHeight);
	
	this->Camera = View(this->PlayerTexture.GetPosition(), Vector2f(Window->getSize().x, Window->getSize().y));
	Window->setView(this->Camera);
}

Character::~Character()
{
}

/// <summary>
/// Updates the players game logic. This includes health, movement, etc...
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
/// <param name = "dt">Delta Time</param>
void Character::Update(RenderWindow* Window, float dt)
{	
	this->HandleRotation(Window);
	this->HandleMovement(Window, dt);
	this->HandleCamera(Window, dt);
}

/// <summary>
/// Renders the character to the screen.
/// </summary>
/// <param name = "Window">The render target.</param>
void Character::Draw(RenderWindow* Window)
{
	this->PlayerTexture.Draw(Window);
}

/// <summary>
/// Handles all the logic for moving the player between two points.
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
/// <param name = "dt">Delta Time</param>
void Character::HandleMovement(RenderWindow* Window, float dt)
{
	this->Offset = Vector2f();
	Vector2f Direction = Vector2f(cos(ToRadians(this->Angle)), sin(ToRadians(this->Angle)));
	
	if (Magnitude(Direction) > 0)
		Direction = Normalise(Direction);

	Vector2f Per = Perpendicular(Direction);

	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		Offset.x += this->PlayerSpeed * Direction.x * dt;
		Offset.y += this->PlayerSpeed * Direction.y * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
		Offset.x -= Per.x * this->StrafeSpeed * dt;
	if (Keyboard::isKeyPressed(Keyboard::Key::D))
		Offset.x += Per.x * this->StrafeSpeed * dt;

	this->PlayerTexture.Move(Offset);
}

/// <summary>
/// Handles the logic for rotating the player.
/// </summary>
/// <param name = "Window">A pointer to the render target. Needed for some logic.</param>
void Character::HandleRotation(sf::RenderWindow * Window)
{
	Vector2i MousePosition = Mouse::getPosition(*Window);

	this->Angle = atan2(Window->getPosition().y - MousePosition.y, Window->getPosition().x - MousePosition.x);
	this->Angle *= (180 / PI);

	if (this->Angle < 360)
		this->Angle += 360;

	this->PlayerTexture.SmartSprite.setRotation(this->Angle + 90);
}

/// <summary>
/// Moves the camera.
/// </summary>
/// <param name = "Window">A pointer to the render target.</param>
/// <param name = "dt">Delta Time</param>
void Character::HandleCamera(RenderWindow* Window, float dt)
{
	this->Camera.move(this->Offset);
	Window->setView(this->Camera);
}
