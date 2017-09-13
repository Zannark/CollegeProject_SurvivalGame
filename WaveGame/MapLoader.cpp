#include "MapLoader.h"

/// <summary>
/// Parses the XML map document.
/// </summary>
/// <param name = "MapFile">The relative path to the map.</param>
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

/// <summary>
/// Loads the map in from the XML file.
/// </summary>
/// <returns>The loaded in map.</returns>
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
		shared_ptr<Prop> P = make_shared<Prop>(PropNode->value());

		///Get the collision information
		xml_attribute<char>* Attribute = PropNode->first_attribute("collides");
		this->CheckAttribute("collides", Attribute);
		P->SetCollision(StringToBool(Attribute->value()));
		
		///Get the location of prop in the world.
		///X
		Vector2f Position(0, 0);
		Attribute = PropNode->first_attribute("x");
		this->CheckAttribute("x", Attribute);
		Position.x = stof(Attribute->value());
		
		///Y
		Attribute = PropNode->first_attribute("y");
		this->CheckAttribute("y", Attribute);
		Position.y = stof(Attribute->value());
		P->SetPosition(Position);

		///Get if the prop is animated or not.
		Attribute = PropNode->first_attribute("type");
		this->CheckAttribute("type", Attribute);
		bool IsStatic = ((Attribute->value() == "static") ? true : false);
		P->SetStatic(IsStatic);

		///If animated 
		if (!IsStatic)
		{
			Attribute = PropNode->first_attribute("delay");
			this->CheckAttribute("delay", Attribute);
			Position.y = stof(Attribute->value());
		}
		
		LoadedMap.AddProp(P);
	}

	return LoadedMap;
}

void MapLoader::CheckAttribute(string AttributeName, xml_attribute<char>* Attribute)
{
	if (!Attribute)
	{
		cerr << "No prop information about" << AttributeName << "." << endl;
		WaitForAnyKeyAndExit();
	}
}
