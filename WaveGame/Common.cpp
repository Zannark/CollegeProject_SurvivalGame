#include "Common.h"

using namespace std;

void WaitForAnyKeyAndExit(int ReturnCode)
{
	cout << "Press any key to continue..." << endl;
	cin.get();
	exit(ReturnCode);
}
