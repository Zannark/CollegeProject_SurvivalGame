#include "GameTexture.h"
#include "Common.h"
#include "MapLoader.h"
#include <SFML\Graphics.hpp>

using namespace sf;

int main(int argc, char** argv)
{
	shared_ptr<RenderWindow> Window = make_shared<RenderWindow>(VideoMode(800, 600, 32), "Game");
	Event E;

	Engine::Core::MapLoader::Load("");

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
		
		Window->display();
	}

	return 0;
}