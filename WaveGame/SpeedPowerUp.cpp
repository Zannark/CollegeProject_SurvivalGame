#include "SpeedPowerUp.h"



Engine::GamePlay::SpeedPowerUp::SpeedPowerUp(Vector2f Position)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache("Assets/SpeedPowerUp.png"));
	this->Texture->SetPosition(Position);
	this->ActiveTime = 2.f;
}

void Engine::GamePlay::SpeedPowerUp::OnUse(Player* P)
{
	if (!this->HasBeenUsed)
	{
		this->HasBeenUsed = true;
		P->SetSpeedModifier(SPEED_BOOST_MULTIPLIER);
	}
}

void Engine::GamePlay::SpeedPowerUp::OnUseEnd(Player* P)
{
	P->SetSpeedModifier(1);
}
