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

}
