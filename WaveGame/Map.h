#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <memory>
#include <tuple>
#include "Animator.h"
#include "VectorMaths.h"

using namespace std;

namespace Engine::Core
{
	using Prop = tuple<shared_ptr<Animator>, bool>;

	class Map
	{
	public:
		Map();
		~Map();

		void AddBackground(string ID);
		void AddProp(string ID, Vector2f Position, bool DoesCollision);
		vector<Prop> GetProps(void);
		bool IsPropAtPosition(Vector2f Position);
		void DrawBackground(RenderWindow* Window);
		void DrawProps(RenderWindow* Window);

	private:
		Animator Background;
		vector<Prop> Props;
	};
}
