#pragma once

#include <vector>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <rapidxml.hpp>
#include "SmartTexture.h"
#include "Prop.h"
#include "Common.h"
#include "Map.h"


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

	void CheckAttribute(string AttributeName, xml_attribute<char>* Attribute);
};

