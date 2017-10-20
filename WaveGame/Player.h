#pragma once

#include <memory>
#include <math.h>
#include <SFML\Graphics.hpp>
#include "Common.h"
#include "Character.h"
#include "GameTexture.h"

using namespace std;
using namespace sf;
using namespace Engine::Core;
using namespace Engine::Misc;

namespace Engine::Gameplay
{
	class Player : public Character
	{
	public:
		Player();
		~Player();

		void Update(shared_ptr<RenderWindow> Window, float dt) override;
	
	private:
		float MovementSpeed;
		
		void HandleMovement(float dt);
		void HandleRotation(shared_ptr<RenderWindow> Window, float dt);
	};
}
