#include "Common.h"

#include "Enemy.h"
#include "Player.h"

#ifdef UNITTEST
#include <doctest\doctest.h>
#endif

using namespace std;
using namespace sf;

///Just for debugging purposes.
namespace
{
	///<summary>
	///Sees if two values are within a range of eachother.
	///Used for the unit testing because floating point numbers can be finicky.
	///</summary>
	///<param name = "x">The value being tested.</param>
	///<param name = "y">The value to compare against.</param>
	///<param name = "Range">The margin of error for floating point. Default is 0.5f</param>
	bool ApproximateEquals(float x, float y, float Range = 0.5f)
	{
		float Lower = y - Range;
		float Upper = y + Range;

		return ((x <= Upper) && (x >= Lower));
	}
#ifdef UNITTEST
	TEST_CASE("Approximate Equals Test")
	{
		CHECK(ApproximateEquals(15.5f, 16.0f, 0.5f));
		CHECK(ApproximateEquals(15.5f, 15.0f, 0.5f));
		CHECK(ApproximateEquals(10.5f, 10.7f, 1.0f));
		CHECK(ApproximateEquals(10.5f, 9.5f, 1.0f));

		CHECK_FALSE(ApproximateEquals(10.5f, 1.0f, 1.0f));
		CHECK_FALSE(ApproximateEquals(10.5f, 90000.5f, 0.0f));
		CHECK_FALSE(ApproximateEquals(10.5f, 9.4f, 1.0f));
		CHECK_FALSE(ApproximateEquals(10.5f, 11.8f, 1.0f));
	}
#endif //UNITTEST
}

namespace Engine::Misc
{
	/// <summary>
	/// Upon a fatal error which cannot be recovered from, this should be called.
	/// Pauses the program and waits for user input before exiting.
	/// </summary>
	/// <param name = "ReturnCode">The return code which should be used upon the program exiting. Defaults to EXIT_FAILURE.</param>
	void WaitForAnyKeyAndExit(int ReturnCode)
	{
		cout << "Press any key to continue..." << endl;
		cin.get();
		exit(ReturnCode);
	}

	/// <Summary>
	/// Converts a string into a boolean.
	/// The string must be either 0, 1, true for false, or false will be returned by default. It is not case sensitive.
	/// </summary>
	/// <param name = "Str">The string to be convtered.</param>
	bool StringToBool(string Str)
	{
		if (Str == "1")
			return true;
		else if (Str == "0")
			return false;

		Str = ToUpper(Str);

		if (Str == "TRUE")
			return true;

		return false;
	}
#ifdef UNITTEST
	TEST_CASE("String To Bool Tests")
	{
		CHECK(StringToBool("TRUE") == true);
		CHECK(StringToBool("true") == true);
		CHECK(StringToBool("TrUe") == true);
		CHECK(StringToBool("1") == true);

		CHECK(StringToBool("Toast") == false);
		CHECK(StringToBool("FALSE") == false);
		CHECK(StringToBool("false") == false);
		CHECK(StringToBool("FaLsE") == false);
		CHECK(StringToBool("0") == false);
	}
#endif //UNITTEST

	/// <Summary>
	/// Turns every letter in a string to a upper case letter.
	/// </summary>
	/// <param name = "Str">The string to be convtered.</param>
	std::string ToUpper(std::string Str)
	{
		string Return;

		for (char C : Str)
			Return += (char)toupper(C);

		return Return;
	}
#ifdef UNITTEST
	TEST_CASE("To Upper Tests")
	{
		CHECK(ToUpper("hello, world!") == "HELLO, WORLD!");
		CHECK(ToUpper("hello, WORLD!") == "HELLO, WORLD!");
		CHECK(ToUpper("HELLO, WORLD!") == "HELLO, WORLD!");
	}
#endif //UNITTEST

	/*// <Summary>
	/// Turns every letter in a string to a lower case letter.
	/// </summary>
	/// <param name = "Str">The string to be convtered.</param>
	std::string ToLower(std::string Str)
	{
		string Return;

		for (char C : Str)
			Return += (char)tolower(C);

		return Return;
	}
#ifdef UNITTEST
	TEST_CASE("To Lower Tests")
	{
		CHECK(ToLower("HELLO, WORLD!") == "hello, world!");
		CHECK(ToLower("hello, WORLD!") == "hello, world!");
		CHECK(ToLower("HELLO, WORLD!") == "hello, world!");
	}
#endif //UNITTEST
	
	///<summary>
	/// Converts degrees into radians.
	///</summary>
	///<param name = "Degrees">The degrees to convert.</param>
	///<returns>The radian value of the given degrees.</returns>
	double ToRadians(double Degrees)
	{
		return Degrees * PI / 180;
	}
#ifdef UNITTEST
	TEST_CASE("Degrees to Radians")
	{
		CHECK(ApproximateEquals(ToRadians(5), 0.087f, 0.2f));
		CHECK(ApproximateEquals(ToRadians(200), 3.4, 0.2f));
		CHECK(ApproximateEquals(ToRadians(360), 6.2, 0.2f));
	}
#endif //UNITTEST

	///<summary>
	/// Converts radians into degrees.
	///</summary>
	///<param name = "Radians">The Radians to convert.</param>
	///<returns>The degree value of the given Radians.</returns>
	double ToDegrees(double Radians)
	{
		return Radians * 180 / PI;
	}
#ifdef UNITTEST
	TEST_CASE("Radians to Degrees")
	{
		CHECK(ApproximateEquals(ToDegrees(1), 57.2f, 0.2f));
		CHECK(ApproximateEquals(ToDegrees(6), 343.7f, 0.2f));
		CHECK(ApproximateEquals(ToDegrees(0.5f), 28.6f, 0.2f));
	}
#endif //UNITTEST*/

	///<summary>
	///Calculates the difference between a and b.
	///</summary>
	double Difference(double a, double b)
	{
		return a - b;
	}
#ifdef UNITTEST
	TEST_CASE("Difference")
	{
		CHECK(Difference(10, 5) == 5);
		CHECK(Difference(10, 2) == 8);
		CHECK(Difference(43, 340) == -297);
	}
#endif //UNITTEST

	///<summary>
	///Works out the euclidean distance between two points.
	///</summary>
	///<param name = "P">The start point.</param>
	///<param name = "Q">The end point.</param>
	float EuclideanDistance(sf::Vector2f P, sf::Vector2f Q)
	{
		float x = pow(P.x - Q.x, 2);
		float y = pow(P.y - Q.y, 2);

		return sqrtf(x + y);
	}
#ifdef UNITTEST
	TEST_CASE("Euclidean Distance Tests")
	{
		CHECK(ApproximateEquals(EuclideanDistance(sf::Vector2f(10, 40), sf::Vector2f(100, 30)), 90.5539f, 0.1f));
		CHECK(ApproximateEquals(EuclideanDistance(sf::Vector2f(15, 600), sf::Vector2f(1, 500)), 100.9752f, 0.1f));
		CHECK(ApproximateEquals(EuclideanDistance(sf::Vector2f(0, 0), sf::Vector2f(50, 45)), 67.2681f, 0.1f));
		CHECK(ApproximateEquals(EuclideanDistance(sf::Vector2f(17, 320), sf::Vector2f(82, 21)), 305.9837f, 0.1f));
	}
#endif

	///<summary>
	///Tests if one vector is smaller than the other.
	///</summary>
	///<param name = "Element1">The first part of the test.</param>
	///<param name = "Element2">The vector to test against element1.</param>
	///<returns>True if element1 is smaller than element2.</returns>
	bool VectorLessThan(Vector2i Element1, Vector2i Element2)
	{
		return (Element1.x < Element2.x) && (Element1.y < Element2.y);
	}
#ifdef UNITTEST
	TEST_CASE("Vector Less Than")
	{
		CHECK(VectorLessThan(sf::Vector2i(0, 1), sf::Vector2i(450, 1080)));
		CHECK(VectorLessThan(sf::Vector2i(1, -1), sf::Vector2i(23, 0)));
		CHECK(VectorLessThan(sf::Vector2i(10, 10), sf::Vector2i(58, 65)));
		CHECK_FALSE(VectorLessThan(sf::Vector2i(10, 10), sf::Vector2i(5, 5)));
	}
#endif //UNITTEST

	bool VectorLessThan(Vector2f Element1, Vector2f Element2)
	{
		return (Element1.x < Element2.x) && (Element1.y < Element2.y);
	}

	bool VectorGreaterThan(sf::Vector2f Element1, sf::Vector2f Element2)
	{
		return (Element1.x > Element2.x) && (Element1.y > Element2.y);
	}

	/*//<summary>
	///Scales a value down to fit between two values.
	///</summary>
	///<param name = "Min">The lowest value which the data can be.</param>
	///<param name = "Max">The highest value the data can be.</param>
	///<param name = "Data">The data to normalise.</param>
	///<returns>The normalised data.</returns>
	float NormaliseToRange(float Min, float Max, float Data)
	{
		return (Data - Min) / (Max - Min);
	}*/

	///<summary>
	///Aligned the player within Nodes.
	///</summary>
	sf::Vector2f AlignPlayer(void* P)
	{
		int AlignedX = (int)(((Player*)P)->GetPosition().x / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;
		int AlignedY = (int)(((Player*)P)->GetPosition().y / NAVIGATION_NODE_DISTANCE) * NAVIGATION_NODE_DISTANCE;

		return Vector2f((float)AlignedX, (float)AlignedY);
	}
}
