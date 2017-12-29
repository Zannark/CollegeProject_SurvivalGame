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

		void MoveToPosition(Vector2f Position, float Speed);
		Vector2f GetPosition(void);
		Vector2f GetSize(void);
		void Draw(RenderWindow* Window);
		void TakeDamage(int Amount);
		bool CheckHealth(void);

		virtual void Update(RenderWindow* Window, Map M, float dt) = 0;
	protected:
		float Angle;
		Vector2f Direction;
		int Health;
		bool IsAlive;

		///Saves the last position where the character could move freely.
		Vector2f LastGoodPosition;
		shared_ptr<GameTexture> Texture;

		void SetPosition(Vector2f Position);
		virtual void UpdateUI(void);
	};
}