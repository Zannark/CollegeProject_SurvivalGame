#include "Common.h"

using namespace std;
using namespace sf;

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
TEST_CASE("String to bool")
{
	CHECK_FALSE(StringToBool("Fail"));
	CHECK(StringToBool("True"));
	CHECK_FALSE(StringToBool("False"));
	CHECK_FALSE(StringToBool("0"));
	CHECK(StringToBool("1"));
	CHECK(StringToBool("TRuE"));
	CHECK(StringToBool("true"));
	CHECK_FALSE(StringToBool("FAlSe"));
	CHECK_FALSE(StringToBool("false"));
}

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
TEST_CASE("String to upper case")
{
	CHECK_FALSE(ToUpper("hello world") == "hello world");
	CHECK(ToUpper("hello world") == "HELLO WORLD");
	CHECK(ToUpper("HELLO WORLD") == "HELLO WORLD");
}

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
TEST_CASE("String to lowercase case")
{
	CHECK_FALSE(ToLower("HELLO WORLD") == "HELLO WORLD");
	CHECK(ToLower("hello world") == "hello world");
	CHECK(ToLower("HELLO WORLD") == "hello world");
}

double ToRadians(double Degrees)
{
	return Degrees * PI / 180;
}

double ToDegrees(double Radians)
{
	return Radians * 180 / PI;
}