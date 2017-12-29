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
	return Vector2f((float)this->Texture->GetSFMLTexture()->getSize().x, (float)this->Texture->GetSFMLTexture()->getSize().y );
}

void Engine::Core::Character::Draw(RenderWindow* Window)
{
	this->Texture->Draw(Window);
}

void Engine::Core::Character::TakeDamage(int Amount)
{
	this->Health -= Amount;
	this->UpdateUI();
}

bool Engine::Core::Character::CheckHealth(void)
{
	if (this->Health <= 0)
		this->IsAlive = false;

	return this->IsAlive;
}

void Engine::Core::Character::SetPosition(Vector2f Position)
{
	this->Texture->SetPosition(Position);
}

void Engine::Core::Character::UpdateUI(void)
{
}
