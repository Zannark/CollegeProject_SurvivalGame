#include "VectorMaths.h"

/// <summary>
/// Gets the distance between two vectors.
/// <summary>
/// <param name = "Vec1">The starting point.</param>
/// <param name = "Vec2">The ending point.</param>
/// <returns>The distance between the two vectors, as a vector</returns>
Vector2f Engine::Core::Distance(Vector2f Vec1, Vector2f Vec2)
{
	return Abs(Vec1 - Vec2);
}

/// <summary>
///	Gets the magnitude, or length, of the vector.
/// </summary>
/// <param name = "Vec">The vector to find the length of</param>
/// <returns>The length of the vector.</returns>
float Engine::Core::Magnitude(Vector2f Vec)
{
	return sqrt((Vec.x * Vec.x) + (Vec.y * Vec.y));
}

/// <summary>
/// Normalises the vector.
/// </summary>
/// <param name = "Vec">The vector to normalise.</param> 
/// <returns>The normalised vector.</returns>
Vector2f Engine::Core::Normalise(Vector2f Vec)
{
	return Vector2f(Vec.x/ Magnitude(Vec), Vec.y / Magnitude(Vec));
}

/// <summary>
/// Gets the dot products of the vector.
/// <summary>
/// <param name = "Vec1">The first vector to find the dot product of.</param>
/// <param name = "Vec2">The second vector to find the dot product of.</param>
float Engine::Core::Dot(Vector2f Vec1, Vector2f Vec2)
{
	return ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
}

/// <summary>
/// Finds the vector perpendicular to the given vector.
/// </summary>
/// <param name = "Vec">The vector to find the perpendicular of.</param>
/// <returns>The purpendicular vector.</returns>
Vector2f Engine::Core::Perpendicular(Vector2f Vec)
{
	return Vector2f(-Vec.y, Vec.x);
}

///<summary>
///Lerps between two points
///</summary>
///<param name = "Start">The point where the lerp starts.</param>
///<param name = "End">The point where the lerp ends.</param>
///<param name = "t">The current progress in the lerp.</param>
///<returns>The current result of lerping.</returns>
Vector2f Engine::Core::Lerp(sf::Vector2f Start, sf::Vector2f End, float t)
{
	return Start + t * (End - Start);
}

///<summary>
///Gets the absolute value of a vector.
///</summary>
///<param name = "Vec">The vector to get the value of.</param>
///<returns>The absolute value.</returns>
Vector2f Engine::Core::Abs(Vector2f Vec)
{
	return Vector2f(fabs(Vec.x), fabs(Vec.y));
}

///<summary>
///Divides the vector by a value.
///</summary>
///<param name = "Vec">The vector to divide.</param>
///<param name = "Factor">The value to divide by.</param>
///<returns>The value of the divided vector.</returns>
Vector2f Engine::Core::Div(Vector2f Vec, float Factor)
{
	return Vector2f(Vec.x / Factor, Vec.y / Factor);
}
