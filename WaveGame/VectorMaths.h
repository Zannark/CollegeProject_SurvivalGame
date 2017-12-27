#pragma once

#include <SFML\Graphics.hpp>
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;

namespace Engine::Core
{
	extern Vector2f Distance(Vector2f Vec1, Vector2f Vec2);
	extern float Magnitude(Vector2f Vec);
	extern Vector2f Normalise(Vector2f Vec);
	extern float Dot(Vector2f Vec1, Vector2f Vec2);
	extern Vector2f Perpendicular(Vector2f Vec);
	extern Vector2f Lerp(sf::Vector2f Start, sf::Vector2f End, float t);
	extern Vector2f Abs(Vector2f Vec);
	extern Vector2f Div(Vector2f Vec, float Factor);
}
