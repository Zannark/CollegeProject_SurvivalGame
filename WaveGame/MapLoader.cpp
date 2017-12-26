#include "MapLoader.h"

Engine::Core::Map Engine::Core::MapLoader::Load(string Path, RenderWindow* Window)
{	
	auto CheckAttribute = [](string AttributeName, xml_attribute<char>* Attribute) -> void 
	{
		if (!Attribute)
		{
			string ErrorMessage = string("No attribute with the name: ") + AttributeName;
			throw runtime_error(ErrorMessage);
		}
	};

	auto GetAttribute = [CheckAttribute](string AttributeName, xml_node<char>* Node) -> string
	{
		xml_attribute<char>* Attribute = Node->first_attribute((char*)AttributeName.c_str());
		CheckAttribute(AttributeName, Attribute);
		return string(Attribute->value());
	};

	xml_document<> MapDocument;
	vector<char> MapContents;

	fstream File(Path);

	if (!File)
	{
		string ErrorMessage = "Failed to open map: " + Path;
		MessageBoxA(Window->getSystemHandle(), ErrorMessage.c_str(), "Error - Map", MB_OK | MB_ICONEXCLAMATION);
		exit(EXIT_FAILURE);
	}

	try
	{
		MapContents = vector<char>((istreambuf_iterator<char>(File)), istreambuf_iterator<char>());
		MapContents.push_back('\0');
		MapDocument.parse<0>(&MapContents[0]);
	}
	catch (parse_error &e)
	{
		throw runtime_error(e.what());
	}

	Map M = Map();
	xml_node<char>* Root = MapDocument.first_node("Map");

	if (!Root)
		throw runtime_error("Failed to find the root node of the map document 'Map'.");

	M.AddBackground(GetAttribute("Background", Root));
	
	///Load in all of the props into the map.
	for (xml_node<char>* PropNode = Root->first_node("Prop"); PropNode; PropNode = PropNode->next_sibling("Prop"))
	{
		///Get the location of prop in the world.
		///X
		Vector2f Position(0, 0);
		Position.x = stof(GetAttribute("X", PropNode));
		///Y
		Position.y = stof(GetAttribute("Y", PropNode));

		M.AddProp(string(PropNode->value()), Position);
	}

	return M;
}
