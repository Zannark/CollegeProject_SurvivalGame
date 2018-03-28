#include "PowerUpBase.h"

///<summary>
///Renders the power up if it hasn't been destroyed or picked up.
///</summary>
///<param name = "Window">A pointer to the RenderWindow to draw to.</param>
void Engine::Core::PowerUpBase::Draw(RenderWindow * Wnd)
{
	if(!this->NeedsToBeDestroyed && !this->HasBeenCollected)
		this->PowerUpAnimation->Draw(Wnd);
}

///<summary>
///Basically constructs the object.
///It's safer to have this here and called from derived classes, rather than have each class make their own.
///This is because C++ doesn't have a generic super, it's compiler specific and I'm only aware of MSVC having it.
///</summary>
void Engine::Core::PowerUpBase::InitBasicPowerUp(void)
{
	this->Timer = 0;
	this->HasBeenCollected = false;
	this->NeedsToBeDestroyed = false;
	this->HasBeenUsed = false;
}

///<summary>
///This is set once the time has ran out, or the player goes over another one while already carrying one.
///</summary>
void Engine::Core::PowerUpBase::SetNeedsToBeDestroyed(void)
{
	this->NeedsToBeDestroyed = true;
}

///<summary>
///Gets the life status of the power up.
///</summary>
///<returns>True if needs to be destroyed, false otherwise.</returns>
bool Engine::Core::PowerUpBase::GetNeedsToBeDestroyed(void)
{
	return this->NeedsToBeDestroyed;
}

///<summary>
///Gets the collection status of the power up.
///</summary>
///<returns>True if picked up, false otherwise.</returns>
bool Engine::Core::PowerUpBase::GetCollected(void)
{
	return this->HasBeenCollected;
}

///<summary>
///Gets the name of the powerup.
///</summary>
///<returns>A string, the name of the powerup.</returns>
string Engine::Core::PowerUpBase::GetPowerUpName(void) const
{
	return this->PowerUpName;
}

///<summary>
///For overriding, would be purely virtual but ran in to errors.
///See derived classes.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::Core::PowerUpBase::OnUse(Player * P)
{
}

///<summary>
///For overriding, would be purely virtual but ran in to errors.
///See derived classes.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::Core::PowerUpBase::OnUseEnd(Player * P)
{
}

///<summary>
///Called once per frame.
///Checks if the player has collided with the powerup and handles that appriatly.
///Also handles the use timer and destruction flag.
///</summary>
///<param name = "P">A pointer to the player.</param>
///<param name = "dt">Delta time.</param>
void Engine::Core::PowerUpBase::Update(Player* P, float dt)
{
	if (!this->HasBeenCollected)
	{
		if (Collision::BoundingBoxTest(*P->GetAnimator()->GetSFMLSprite(), *this->PowerUpAnimation->GetSFMLSprite()))
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
