#include "DamagePowerUp.h"

DamagePowerUp::DamagePowerUp(Vector2f Position)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache("Assets/DamagePowerUp.png"));
	this->Texture->SetPosition(Position);
	this->ActiveTime = 1.5f;
	this->PowerUpName = "Damage Boost";
}

void Engine::GamePlay::DamagePowerUp::OnUse(Player * P)
{
	if (!this->HasBeenUsed)
	{
		P->SetDamageModifier(2);
		this->HasBeenUsed = true;
	}
}

void Engine::GamePlay::DamagePowerUp::OnUseEnd(Player * P)
{
	P->SetDamageModifier(1);
}


