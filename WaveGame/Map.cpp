#include "Map.h"

Engine::Core::Map::Map()
{
}

Engine::Core::Map::~Map()
{
}

void Engine::Core::Map::AddProp(string ID, Vector2f Position)
{
	GameTexture Tex = GameTexture(ID);
	Tex.SetPosition(Position);
	this->Props.push_back(Tex);
}

void Engine::Core::Map::DrawBackground(shared_ptr<RenderWindow> Window)
{
	this->Background.Draw(Window);
}

void Engine::Core::Map::DrawProps(shared_ptr<RenderWindow> Window)
{
	for (auto Prop : this->Props)
		Prop.Draw(Window);
}
