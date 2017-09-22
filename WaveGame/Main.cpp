#include <iostream>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include "TextureCache.h"
#include "Common.h"
#include "GameTime.h"
#include "MapLoader.h"
#include "Character.h"
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
	Character Char = Character(Window);

	cout << ToPixels(1) << endl;
	cout << ToMeters(3779.5275590551) << endl;
	
	while (Window->isOpen())
	{
		Event E;
		while (Window->pollEvent(E))
		{
			if (E.type == Event::Closed)
				Window->close();
		}
				
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