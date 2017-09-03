#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include "SmartTexture.h"
#include "Prop.h"
#include "pugixml.hpp"
#include "Common.h"
#include "Map.h"

using namespace pugi;
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
	vector<Prop> MapProps;
	xml_parse_result ParseResult;
	xml_document MapDocument;
};

