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

/// <summary>
/// Finds all the points (corners) on a texture.
/// </summary>
/// <param name = "Texture">The texture to find the points on.</param>
/// <returns>The points.</returns>
vector<Vector2f> GetPoints(SmartTexture& Texture)
{
	Vector2u Dimensions = Texture.GetDimensions();
	Vector2f Position = Texture.GetPosition();
	vector<Vector2f> Points = vector<Vector2f>(4);

	Points[0] = Position;
	Points[1] = Vector2f(Position.x + Dimensions.x, Position.y);
	Points[2] = Vector2f(Position.x, Position.y + Dimensions.y);
	Points[3] = Vector2f(Position.x + Dimensions.x, Position.y + Dimensions.y);

	return Points;
}
