#include "MapLoader.h"

Engine::Core::Map Engine::Core::MapLoader::Load(string Path)
{
	xml_document<> MapDocument;
	vector<char> MapContents;

	fstream File(Path);

	if (!File)
	{
		string ErrorMessage = string("Failed to open file: ") + Path;
		throw runtime_error(ErrorMessage);
	}
	
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

	Map M = Map();

	xml_node<char>* Root = MapDocument.first_node("Map");
	
	string BackgroundID = GetAttribute("Background", Root);
	cout << BackgroundID << endl;

	return M;
}
