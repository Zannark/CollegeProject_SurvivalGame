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

/// <summary>
/// Adds a prop to the world.
/// </summary>
/// <param name = "Prop">The prop to add.</param>
void Map::AddProp(shared_ptr<Prop> Prop)
{
	this->MapProps.push_back(Prop);
}

/// <summary>
/// Renders all the props, and the background, to the screen.
/// </summary>
/// <param name = "Window">The rende target.</param>
void Map::Draw(RenderWindow* Window)
{
	this->Background.Draw(Window);

	for (shared_ptr<Prop> P : this->MapProps)
		P->Draw(Window);
}

void Map::Update(RenderWindow* Window, Character& P, float dt)
{
	this->HandleCollision(Window, P, dt);
}

/// <summary>
/// Returns all the props in the world that has a certain tag.
/// </summary>
/// <param name = "Tag">The tag to find props with.</param>
/// <returns>The props with that tag.</returns>
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

void Map::HandleCollision(RenderWindow* Window, Character& P, float dt)
{
	/// For now I will iterate over every prop in the map.
	/// This isn't ideal, it's too slow for large maps.
	/// But our current map has 1 prop, so it's all good in the hood.
	
	for (shared_ptr<Prop> Prop : this->MapProps)
	{
		if(Prop->GetCollision())
			P.SetCanMove(!Collision::BoundingBoxTest(Prop->GetTexture().SmartSprite, P.GetTexture().SmartSprite));
	}
}
