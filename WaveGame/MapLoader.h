#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif ///_WIN32

#include <string>
#include <vector>
#include <fstream>
#include <rapidxml.hpp>
#include <exception>
#include <iostream>
#include <memory>
#include <SFML\Config.hpp>
#include "Map.h"
#include "Common.h"

using namespace rapidxml;
using namespace std;

namespace Engine::Core
{
	///<summary>
	///Responsible for loading a map in from XML.
	///</summary>
	class MapLoader
	{
	public:
		static Map Load(string Path, RenderWindow* Window);
	};
}