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

void Engine::Core::Character::SetPosition(Vector2f Position)
{
	this->Texture->SetPosition(Position);
}

void Engine::Core::Character::VectorToDirection(Vector2f& Vec)
{
	Vec = Normalise(Vec);

	if (isnan(this->Direction.x))
		Vec.x = 0;
	if (isnan(this->Direction.y))
		Vec.y = 0;

	if (this->Direction.x > 0)
		Vec.x = 1;
	else if (this->Direction.x < 0)
		Vec.x = -1;

	if (this->Direction.y > 0)
		Vec.y = 1;
	else if (this->Direction.y < 0)
		Vec.y = -1;
}
