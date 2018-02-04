#include "DamagePowerUp.h"

DamagePowerUp::DamagePowerUp(Vector2f Position)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache("Assets/DamagePowerUp.png"));
	this->Texture->SetPosition(Position);
	this->ActiveTime = 1.5f;
	this->PowerUpName = "Damage Boost";
}

///<summary>
///Called when the player presses the PowerUp use key.
///Changes the players damage modifier.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::GamePlay::DamagePowerUp::OnUse(Player * P)
{
	if (!this->HasBeenUsed)
	{
		P->SetDamageModifier(DAMAGE_BOOST_MULTIPLIER);
		this->HasBeenUsed = true;
	}
}

///<summary>
///Called when the power up is out of time.
///Changes the players damage modifier.
///</summary>
///<param name = "P">A pointer to the player.</param>
void Engine::GamePlay::DamagePowerUp::OnUseEnd(Player * P)
{
	P->SetDamageModifier(1);
}


