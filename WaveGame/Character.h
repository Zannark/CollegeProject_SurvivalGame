#pragma once

#include <iostream>
#include <memory>
#include "GameTexture.h"

using namespace std;

namespace Engine::Core
{
	class Character
	{
	public:
		Character();
		~Character();

		Vector2f GetPosition(void);
		void Draw(shared_ptr<RenderWindow> Window);

		virtual void Update(shared_ptr<RenderWindow> Window, float dt) = 0;

	protected:
		float Angle;
		shared_ptr<GameTexture> Texture;
	};
}