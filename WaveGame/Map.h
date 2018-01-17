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

		void AddBackground(string ID);
		void AddProp(string ID, Vector2f Position);
		vector<shared_ptr<GameTexture>> GetProps(void);
		bool IsPropAtPosition(Vector2f Position);
		void DrawBackground(RenderWindow* Window);
		void DrawProps(RenderWindow* Window);

	private:
		GameTexture Background;
		vector<shared_ptr<GameTexture>> Props;
	};
}
