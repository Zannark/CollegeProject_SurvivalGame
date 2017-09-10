#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include "SmartTexture.h"
#include "Prop.h"
#include "Common.h"
#include "Map.h"
#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

/// <summary>
/// Responisble for loading in the map from XML files.
/// </summary>
class MapLoader
{
public:
	MapLoader(string MapFile);
	~MapLoader();

	Map Load();

private:
	xml_document<> MapDocument;
	vector<char> MapContents;
};

