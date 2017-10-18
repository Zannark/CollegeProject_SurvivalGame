#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <memory>
#include "GameTexture.h"

using namespace std;

namespace Engine::Core
{
	class Map
	{
	public:
		Map();
		~Map();

		void AddProp(string ID, Vector2f Position);

		void DrawBackground(shared_ptr<RenderWindow> Window);
		void DrawProps(shared_ptr<RenderWindow> Window);
	private:
		GameTexture Background;
		vector<GameTexture> Props;
	};
}
