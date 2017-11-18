#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <rapidxml.hpp>
#include <exception>
#include <iostream>
#include "Map.h"
#include "Common.h"

using namespace rapidxml;
using namespace std;

namespace Engine::Core
{
	class MapLoader
	{
	public:
		static Map Load(string Path);
	};
}