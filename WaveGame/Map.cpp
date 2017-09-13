#include "Map.h"

Map::Map()
{
}

Map::Map(Vector2f Dimensions, string BackgroundID)
{
	this->MapDimensions = Dimensions;
	this->Background = TextureCache::GetTexure(BackgroundID);
}


Map::~Map()
{
}

void Map::AddProp(shared_ptr<Prop> Prop)
{
	this->MapProps.push_back(Prop);
}

void Map::Draw(RenderWindow * Window)
{
	this->Background.Draw(Window);

	for (shared_ptr<Prop> P : this->MapProps)
		P->Draw(Window);
}

vector<shared_ptr<Prop>> Map::GetPropsWithTag(string Tag)
{
	vector<shared_ptr<Prop>> Props;

	for (shared_ptr<Prop> P : this->MapProps)
	{
		if (P->GetTag() == Tag)
			Props.push_back(P);
	}

	return Props;
}
