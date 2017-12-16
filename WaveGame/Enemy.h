#pragma once

#include <memory>
#include "GameTexture.h"
#include "Character.h"
#include "Common.h"

using namespace Engine::Misc;
using namespace Engine::Core;
using namespace std;

namespace Engine::GamePlay
{
	class Enemy : public Character
	{
	public:
		Enemy(Vector2f Position);
		~Enemy();

		void Update(shared_ptr<RenderWindow> Window, Map M, float dt);

	private:
		void CalculateNextNode();
	};
}