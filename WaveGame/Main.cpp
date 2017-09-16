#include <iostream>
#include <SFML\Graphics.hpp>
#include "TextureCache.h"
#include "Common.h"
#include "GameTime.h"
#include "MapLoader.h"
#include "Character.h"

using namespace std;
using namespace sf;

int main(void)
{
	TextureCache::Init();
	GameTime::Init();	
	MapLoader Load("Test.xml");
	Map M = Load.Load();
	Character Char = Character();
		
	RenderWindow *Window = new RenderWindow(VideoMode(800, 600, 32), "Test Window");
	while (Window->isOpen())
	{
		Event E;
		while (Window->pollEvent(E))
		{
			if (E.type == Event::Closed)
				Window->close();
		}

		//cout << GameTime::DeltaTime() << endl;
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