#include "Common.h"

using namespace std;

void WaitForAnyKeyAndExit(int ReturnCode)
{
	cout << "Press any key to continue..." << endl;
	cin.get();
	exit(ReturnCode);
}

bool StringToBool(string Bool)
{
	if (Bool == "1")
		return true;
	else if (Bool == "0")
		return false;

	Bool = ToUpper(Bool);

	if (Bool == "TRUE")
		return true;

	return false;
}

std::string ToUpper(std::string Str)
{
	string Return;

	for (char C : Str)
		Return += (char)toupper(C);

	return Return;
}

std::string ToLower(std::string Str)
{
	string Return;

	for (char C : Str)
		Return += (char)tolower(C);

	return Return;
}
