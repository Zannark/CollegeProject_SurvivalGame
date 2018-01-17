#include "Map.h"

Engine::Core::Map::Map()
{
}

Engine::Core::Map::~Map()
{
}

///<summary>
///Sets what the background texture is for the map.
///</summary>
///<param name = "ID">A string which is the ID of the texture for the background.</param>
void Engine::Core::Map::AddBackground(string ID)
{
	this->Background = TextureCache::Cache.Access(ID);
}

///<summary>
///Adds a prop to the Props vector, so they can be drawn.
///</summary>
///<param name = "ID">A string which is the ID for the texture.</param>
///<param name = "Position">A Vector2f which contains the on screen position for the prop.</param>
void Engine::Core::Map::AddProp(string ID, Vector2f Position)
{
	shared_ptr<GameTexture> Tex = make_shared<GameTexture>(TextureCache::Cache.Access(ID));
	Tex->SetPosition(Position);
	this->Props.push_back(Tex);
}

///<summary>
///Gets all props which are loaded into the map.
///</summary>
///<returns>The props which are loaded in the map.</returns>
vector<shared_ptr<Engine::Core::GameTexture>> Engine::Core::Map::GetProps(void)
{
	return this->Props;
}

///<summary>
///Checks if there is an prop at the given position.
///</summary>
///<param name = "Position">The position to see if there is a prop there.</param>
///<returns>True if there is a prop, false otherwise.</returns>
bool Engine::Core::Map::IsPropAtPosition(Vector2f Position)
{
	return true;
}

///<summary>
///Draws the background. The background is the first thing which should be drawn.
///This ensures that the props, player and enemies are on top of it.
///</summary>
///<param name = "Window">A pointer to the RenderWindow is being drawn to.</param>
void Engine::Core::Map::DrawBackground(RenderWindow* Window)
{
	this->Background.Draw(Window);
}

///<summary>
///Draws the prop to the screen.
///</summary>
///<param name = "Window">A pointer to the RenderWindow is being drawn to.</param>
void Engine::Core::Map::DrawProps(RenderWindow* Window)
{
	for (auto Prop : this->Props)
		Prop->Draw(Window);
}
