#pragma once

#include <SFML\Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

namespace Engine::Core
{
	extern Vector2f Distance(Vector2f Vec1, Vector2f Vec2);
	extern float Magnitude(Vector2f Vec);
	extern Vector2f Normalise(Vector2f Vec);
	extern float Dot(Vector2f Vec1, Vector2f Vec2);
	extern Vector2f Perpendicular(Vector2f Vec);
}
