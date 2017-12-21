#pragma once

#include <iostream>
#include <memory>
#include "GameTexture.h"
#include "Map.h"
#include "VectorMaths.h"

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

		virtual void Update(shared_ptr<RenderWindow> Window, Map M, float dt) = 0;

	protected:
		float Angle;
		Vector2f Direction;

		///Saves the last position where the character could move freely.
		Vector2f LastGoodPosition;
		shared_ptr<GameTexture> Texture;

		void SetPosition(Vector2f Position);

		void VectorToDirection(Vector2f& Vec);
	};
}