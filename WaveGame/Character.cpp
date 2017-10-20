#include "Character.h"



Engine::Core::Character::Character()
{
}


Engine::Core::Character::~Character()
{
}

Vector2f Engine::Core::Character::GetPosition(void)
{
	return this->Texture->GetSFMLSprite()->getPosition();
}

void Engine::Core::Character::Draw(shared_ptr<RenderWindow> Window)
{
	this->Texture->Draw(Window);
}
