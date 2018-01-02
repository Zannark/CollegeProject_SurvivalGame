#include "Character.h"

Engine::Core::Character::Character()
{
}

Engine::Core::Character::~Character()
{
}

///<summary>
///Gets the position in a sf::Vector2f.
///</summary>
///<returns>The position as a sf::Vector2f.</returns>
Vector2f Engine::Core::Character::GetPosition(void)
{
	return this->Texture->GetSFMLSprite()->getPosition();
}

///<summary>
///Gets the size of the SFML Texture, as a Vector2f.
///</summary>
///<returns>The size of the Texture.</returns>
Vector2f Engine::Core::Character::GetSize(void)
{
	return Vector2f((float)this->Texture->GetSFMLTexture()->getSize().x, (float)this->Texture->GetSFMLTexture()->getSize().y );
}

///<summary>
///Renders the GameTexture to the given RenderWindow.
///</summary>
///<param name = "Window">A pointer to the RenderWindow, which is the target.</param>
void Engine::Core::Character::Draw(RenderWindow* Window)
{
	this->Texture->Draw(Window);
}

///<summary>
///Lowers the amount of health the Character.
///</summary>
///<param name = "Amount">The amount of damage which is given to their health (as an integer).</param>
void Engine::Core::Character::TakeDamage(int Amount)
{
	this->Health -= Amount;
}

///<summary>
///Checks if the health of the current health is above 0.
///</summary>
///<returns>True if the health is above 0, false otherwise.</returns>
bool Engine::Core::Character::CheckHealth(void)
{
	if (this->Health <= 0 && this->IsAlive)
		this->IsAlive = false;

	return this->IsAlive;
}

///<summary>
///Sets the position of the player, within 2D space.
///</summary>
///<param name = "Position">The position to set the Texture in.</param>
void Engine::Core::Character::SetPosition(Vector2f Position)
{
	this->Texture->SetPosition(Position);
}
