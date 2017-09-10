#include <iostream>
#include <SFML\Graphics.hpp>
#include "Common.h"
#include "GameTime.h"
#include "MapLoader.h"

using namespace std;
using namespace sf;

int main(void)
{
	GameTime::Init();	
	MapLoader Load("Test.xml");
	Load.Load();

	StringToBool("true");

	RenderWindow *Window = new RenderWindow(VideoMode(800, 600, 32), "Test Window");
	while (Window->isOpen())
	{
		Event E;
		while (Window->pollEvent(E))
		{
			if (E.type == Event::Closed)
				Window->close();
		}

		Window->clear();



		Window->display();
		GameTime::Update();
	}

	delete Window;
	return 0;
}