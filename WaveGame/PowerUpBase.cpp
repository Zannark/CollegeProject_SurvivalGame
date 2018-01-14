#include "PowerUpBase.h"

void Engine::Core::PowerUpBase::Draw(RenderWindow * Wnd)
{
	cout << "Called" << endl;
	if(!this->NeedsToBeDestroyed && !this->HasBeenCollected)
		this->Texture->Draw(Wnd);
}

void Engine::Core::PowerUpBase::InitBasicPowerUp(void)
{
	cout << "called" << endl;
	this->Timer = 0;
	this->HasBeenCollected = false;
	this->NeedsToBeDestroyed = false;
	this->HasBeenUsed = false;
}

bool Engine::Core::PowerUpBase::GetNeedsToBeDestroyed(void)
{
	return this->NeedsToBeDestroyed;
}

void Engine::Core::PowerUpBase::Update(Player* P, float dt)
{
	if (!this->HasBeenCollected)
	{
		if (Collision::BoundingBoxTest(*P->GetGameTexure()->GetSFMLSprite(), *this->Texture->GetSFMLSprite()))
		{
			this->HasBeenCollected = true;
			P->SetPowerUp((void*)this);
		}
	}
	else if(this->HasBeenCollected && !this->NeedsToBeDestroyed && this->HasBeenUsed)
	{
		this->Timer += dt;

		if (this->Timer >= this->ActiveTime)
			this->NeedsToBeDestroyed = true;
	}
}
