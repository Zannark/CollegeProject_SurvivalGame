#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <memory>
#include "Animator.h"
#include "VectorMaths.h"

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
		vector<shared_ptr<Animator>> GetProps(void);
		bool IsPropAtPosition(Vector2f Position);
		void DrawBackground(RenderWindow* Window);
		void DrawProps(RenderWindow* Window);

	private:
		Animator Background;
		vector<shared_ptr<Animator>> Props;
	};
}
