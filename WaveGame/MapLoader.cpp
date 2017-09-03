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

	this->ParseResult = this->MapDocument.load_file(MapFile.c_str());
}


MapLoader::~MapLoader()
{
}

Map MapLoader::Load()
{
	Map LoadedMap;

	for(xml_node_iterator Iter = )

	return LoadedMap;
}
