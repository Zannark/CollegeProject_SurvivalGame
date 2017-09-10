#include "MapLoader.h"

/// <summary>
/// Parses the XML map document.
/// </summary>
/// <Param name = "MapFile">The relative path to the map.</Param>
MapLoader::MapLoader(string MapFile)
{
	FS::path MapPath(MapFile);
	if (!FS::exists(MapPath))
		throw runtime_error("Failed to locate map file " + MapFile);

	ifstream File(MapFile);

	try
	{
		this->MapContents = vector<char>((istreambuf_iterator<char>(File)), istreambuf_iterator<char>());
		this->MapContents.push_back('\0');
		this->MapDocument.parse<0>(&this->MapContents[0]);
	}
	catch (parse_error &e)
	{
		cerr << "Rapid XML has thrown a parsing error with map \"" << MapFile << "\" " << e.what() << endl;
		WaitForAnyKeyAndExit();
	}
}

MapLoader::~MapLoader()
{
}

Map MapLoader::Load()
{
	Map LoadedMap;

	xml_node<char>* RootNode = this->MapDocument.first_node("Map");

	if (!RootNode)
	{
		cerr << "Failed to find the root node in the map." << endl;
		WaitForAnyKeyAndExit();
	}

	float Width = stof(string(RootNode->first_attribute("width")->value()));
	float Height = stof(string(RootNode->first_attribute("height")->value()));
	LoadedMap = Map(Vector2f(Width, Height));
	
	///Load in all of the props into the map.
	for (xml_node<char>* PropNode = RootNode->first_node("Prop"); PropNode; PropNode = PropNode->next_sibling("Prop"))
	{
		
	}

	return LoadedMap;
}
