#include "SpeedPowerUp.h"



Engine::GamePlay::SpeedPowerUp::SpeedPowerUp(Vector2f Position)
{
	this->Texture = make_shared<GameTexture>(TextureCache::Cache("Assets/SpeedPowerUp.png"));
	this->ActiveTime = 1.5f;
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
	P->SetSpeedModifier(0);
}

/*void Engine::GamePlay::SpeedPowerUp::Update(Player* P, float dt)
{
	PowerUpBase::Update(P, dt);
}*/



