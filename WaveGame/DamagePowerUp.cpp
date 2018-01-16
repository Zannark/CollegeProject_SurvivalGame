#include "DamagePowerUp.h"

DamagePowerUp::DamagePowerUp(Vector2f Position)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache("Assets/DamagePowerUp.png"));
	this->Texture->SetPosition(Position);
	this->ActiveTime = 2.f;
	this->PowerUpName = "Speed Boost";
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


