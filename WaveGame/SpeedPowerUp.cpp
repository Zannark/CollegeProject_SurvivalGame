#include "SpeedPowerUp.h"

///<summary>
///Constructs the SpeedPowerUp object.
///Loads in the Animator from the AnimationCache.
///</summary>
///<param name = "Position">The position to set the powerup.</param>
Engine::GamePlay::SpeedPowerUp::SpeedPowerUp(Vector2f Position)
{
	this->PowerUpAnimation = make_shared<Animator>(AnimationCache::Cache("Assets/SpeedPowerUp.png"));
	this->PowerUpAnimation->SetPosition(Position);
	this->ActiveTime = 2.f;
	this->PowerUpName = "Speed Boost";
}

///<summary>
///Called when the player presses the PowerUp use key.
///Changes the players speed modifier.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::GamePlay::SpeedPowerUp::OnUse(Player* P)
{
	if (!this->HasBeenUsed)
	{
		this->HasBeenUsed = true;
		P->SetSpeedModifier(SPEED_BOOST_MULTIPLIER);
	}
}

///<summary>
///Called when the power up is out of time.
///Changes the players speed modifier.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::GamePlay::SpeedPowerUp::OnUseEnd(Player* P)
{
	P->SetSpeedModifier(1);
}
