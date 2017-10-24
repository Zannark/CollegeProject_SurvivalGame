#include "Map.h"

Engine::Core::Map::Map()
{
}

Engine::Core::Map::~Map()
{
}

void Engine::Core::Map::AddBackground(string ID)
{
	this->Background = TextureCache::Cache.Access(ID);
}

void Engine::Core::Map::AddProp(string ID, Vector2f Position)
{
	shared_ptr<GameTexture> Tex = make_shared<GameTexture>(TextureCache::Cache.Access(ID));
	Tex->SetPosition(Position);
	this->Props.push_back(Tex);
}

vector<shared_ptr<Engine::Core::GameTexture>> Engine::Core::Map::GetProps(void)
{
	return this->Props;
}

void Engine::Core::Map::DrawBackground(shared_ptr<RenderWindow> Window)
{
	this->Background.Draw(Window);
}

void Engine::Core::Map::DrawProps(shared_ptr<RenderWindow> Window)
{
	for (auto Prop : this->Props)
		Prop->Draw(Window);
}
