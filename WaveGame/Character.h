#pragma once

#include <iostream>
#include "GameTexture.h"

using namespace std;

namespace Engine::Core
{
	class Character
	{
	public:
		Character();
		~Character();

		

	protected:
		float Angle;
		GameTexture Texture;
	};
}