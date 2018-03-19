#pragma once

#include <iostream>
#include <memory>
#include "Animator.h"
#include "Map.h"
#include "VectorMaths.h"

using namespace std;

namespace Engine::Core
{
	///<summary>
	///The base class for enemies and the player to inherit from.
	///Provides common functions, procedures, and attributes.
	///</summary>
	class Character
	{
	public:
		Character();
		~Character();

		Vector2f GetPosition(void);
		Vector2f GetSize(void);
		void Draw(RenderWindow* Window);
		virtual void TakeDamage(int Amount);
		bool CheckHealth(void);
		shared_ptr<Animator> GetAnimator(void) const;

		virtual void Update(RenderWindow* Window, Map M, float dt) = 0;
	protected:
		float Angle;
		int Health;
		bool IsAlive;

		shared_ptr<Animator> CharacterAnimator;

		void SetPosition(Vector2f Position);
	};
}