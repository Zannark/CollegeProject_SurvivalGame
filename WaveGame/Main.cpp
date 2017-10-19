#include "GameTexture.h"
#include "Common.h"
#include "MapLoader.h"
#include <SFML\Graphics.hpp>

using namespace sf;

int main(int argc, char** argv)
{
	Engine::Core::InitTextureCache();
	shared_ptr<RenderWindow> Window = make_shared<RenderWindow>(VideoMode(800, 600, 32), "Game");
	Event E;

	Engine::Core::Map M = Engine::Core::MapLoader::Load("Test.xml");

	while (Window->isOpen())
	{
		while (Window->pollEvent(E))
		{
			if(E.type == Event::Closed)
			{
				Window->close();
			}
		}

		Window->clear(Color::Cyan);
		M.DrawBackground(Window);
		M.DrawProps(Window);
		Window->display();
	}

	return 0;
}