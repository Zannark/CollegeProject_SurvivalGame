#include <iostream>
#include <SFML\Graphics.hpp>
#include "TextureCache.h"
#include "Common.h"
#include "GameTime.h"
#include "MapLoader.h"
#include "Player.h"
#include "Unittest.h"

using namespace std;
using namespace sf;

#ifndef UNITTEST

int main(void)
{
	TextureCache::Init();
	GameTime::Init();	
	MapLoader Load("Test.xml");
	Map M = Load.Load();
		
	RenderWindow *Window = new RenderWindow(VideoMode(1024, 720, 32), "Test Window");
	Player Char = Player(Window);

	while (Window->isOpen())
	{
		Event E;
		while (Window->pollEvent(E))
		{
			if (E.type == Event::Closed)
				Window->close();
		}
		
		M.Update(Window, Char, GameTime::DeltaTime());
		Char.Update(Window, GameTime::DeltaTime());

		Window->clear();
		M.Draw(Window);
		Char.Draw(Window);
		Window->display();
		GameTime::Update();
	}

	delete Window;
	return 0;
}

#else

#include <iostream>
#include <doctest\doctest.h>

using namespace std;

int main(int argc, char** argv)
{
	doctest::Context Context;

	Context.setOption("abort-after", 10);
	Context.setOption("order-by", "name");
	Context.setOption("no-breaks", true);
	Context.applyCommandLine(argc, argv);
	
	Context.run();

	cin.get();
	return 0;
}

#endif // !UNITTEST