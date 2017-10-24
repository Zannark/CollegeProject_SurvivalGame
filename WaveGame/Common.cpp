#include "Common.h"

#ifdef UNITTEST
#include <doctest\doctest.h>
#endif

using namespace std;
using namespace sf;

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
#endif // !UNITTEST

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
#endif // !UNITTEST

	/// <Summary>
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
#endif // !UNITTEST
	
	///<summary>
	/// Converts degrees into radians.
	///</summary>
	///<param name = "Degrees">The degrees to convert.</param>
	///<returns>The radian value of the given degrees.</returns>
	double ToRadians(double Degrees)
	{
		return Degrees * PI / 180;
	}

	///<summary>
	/// Converts radians into degrees.
	///</summary>
	///<param name = "Radians">The Radians to convert.</param>
	///<returns>The degree value of the given Radians.</returns>
	double ToDegrees(double Radians)
	{
		return Radians * 180 / PI;
	}
}
