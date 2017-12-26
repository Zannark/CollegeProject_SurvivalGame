#pragma once

#include <memory>
#include <math.h>
#include <map>
#include <SFML\Graphics.hpp>
#include "Common.h"
#include "Character.h"
#include "GameTexture.h"
#include "Map.h"
#include "SFML_Collision.h"
#include "VectorMaths.h"

using namespace std;
using namespace sf;
using namespace Engine::Core;
using namespace Engine::Misc;

namespace Engine::GamePlay
{
	class Player : public Character
	{
	public:
		Player();
		~Player();

		void Update(RenderWindow* Window, Map M, float dt) override;
		void TakeDamage(int Amount);
	private:
		float MovementSpeed;
		
		void HandleMovement(RenderWindow* Window, Map M, float dt);
		void HandleRotation(RenderWindow* Window, float dt);
		bool CheckCollision(Map M);
		bool CheckHealth(void);
	};
}
