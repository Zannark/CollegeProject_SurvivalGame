#include "VectorMaths.h"

/// <summary>
/// Gets the distance between two vectors.
/// <summary>
/// <param name = "Vec1">The starting point.</param>
/// <param name = "Vec2">The ending point.</param>
/// <returns>The distance between the two vectors, as a vector</returns>
Vector2f Distance(Vector2f Vec1, Vector2f Vec2)
{
	return Vec1 - Vec2;
}

/// <summary>
///	Gets the magnitude, or length, of the vector.
/// </summary>
/// <param name = "Vec">The vector to find the length of</param>
/// <returns>The length of the vector.</returns>
float Magnitude(Vector2f Vec)
{
	return sqrt((Vec.x * Vec.x) + (Vec.y * Vec.y));
}

/// <summary>
/// Normalises the vector.
/// </summary>
/// <param name = "Vec">The vector to normalise.</param> 
/// <returns>The normalised vector.</returns>
Vector2f Normalise(Vector2f Vec)
{
	return Vector2f(Vec.x/ Magnitude(Vec), Vec.y / Magnitude(Vec));
}

/// <summary>
/// Gets the dot products of the vector.
/// <summary>
/// <param name = "Vec1">The first vector to find the dot product of.</param>
/// <param name = "Vec2">The second vector to find the dot product of.</param>
float Dot(Vector2f Vec1, Vector2f Vec2)
{
	return ((Vec1.x * Vec2.x) + (Vec1.y * Vec2.y));
}