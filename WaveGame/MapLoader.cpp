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
	
	///Get map information
	///Width
	float Width = stof(string(this->GetAttribute("width", RootNode)));	
	
	///Height
	float Height = stof(this->GetAttribute("height", RootNode));

	///Background
	string BackgroundID = this->GetAttribute("background", RootNode);
	LoadedMap = Map(Vector2f(Width, Height), BackgroundID);
	
	///Load in all of the props into the map.
	for (xml_node<char>* PropNode = RootNode->first_node("Prop"); PropNode; PropNode = PropNode->next_sibling("Prop"))
	{
		shared_ptr<Prop> P = make_shared<Prop>(PropNode->value());

		///Get the collision information
		P->SetCollision(StringToBool(this->GetAttribute("collides", PropNode)));
		
		///Get the location of prop in the world.
		///X
		Vector2f Position(0, 0);
		Position.x = stof(this->GetAttribute("x", PropNode));
		
		///Y
		Position.y = stof(this->GetAttribute("y", PropNode));
		P->SetPosition(Position);

		///Get if the prop is animated or not.
		bool IsStatic = ((ToUpper(this->GetAttribute("type", PropNode)) == "STATIC") ? true : false);
		P->SetStatic(IsStatic);

		///If animated 
		if (!IsStatic)
			 P->SetAnimationDelay(stof(this->GetAttribute("delay", PropNode)));
		
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

string MapLoader::GetAttribute(string AttributeName, xml_node<char>* Node)
{
	xml_attribute<char>* Attribute = Node->first_attribute((char*)AttributeName.c_str());
	this->CheckAttribute(AttributeName, Attribute);
	return string(Attribute->value());
}
