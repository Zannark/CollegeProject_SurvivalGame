#include "Character.h"

Engine::Core::Character::Character()
{
}


Engine::Core::Character::~Character()
{
}

void Engine::Core::Character::MoveToPosition(Vector2f Position, float Speed)
{
	this->SetPosition(Lerp(this->GetPosition(), Position, Speed));
}

Vector2f Engine::Core::Character::GetPosition(void)
{
	return this->Texture->GetSFMLSprite()->getPosition();
}

Vector2f Engine::Core::Character::GetSize(void)
{
	return Vector2f(this->Texture->GetSFMLTexture()->getSize().x, this->Texture->GetSFMLTexture()->getSize().y );
}

void Engine::Core::Character::Draw(RenderWindow* Window)
{
	this->Texture->Draw(Window);
}

void Engine::Core::Character::SetPosition(Vector2f Position)
{
	this->Texture->SetPosition(Position);
}
