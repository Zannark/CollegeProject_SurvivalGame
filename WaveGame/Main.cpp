#include <iostream>
#include <SFML\Graphics.hpp>
#include "GameTime.h"

using namespace std;
using namespace sf;

int main(void)
{
	RenderWindow *Window = new RenderWindow(VideoMode(800, 600, 32), "Test Window");
	GameTime::Init();
			
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