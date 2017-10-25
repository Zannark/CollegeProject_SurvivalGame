#include "GameTexture.h"
#include "Common.h"
#include "MapLoader.h"
#include "Player.h"
#include "GameTime.h"
#include "NavigationMesh.h"
#include <SFML\Graphics.hpp>

using namespace sf;

#ifndef UNITTEST

int main(int argc, char** argv)
{
	Engine::Core::InitTextureCache();
	shared_ptr<RenderWindow> Window = make_shared<RenderWindow>(VideoMode(800, 600, 32), "Game");
	Event E;
	
	Engine::Gameplay::Player P = Engine::Gameplay::Player();
	Engine::Core::Map M = Engine::Core::MapLoader::Load("Test.xml");

	NavigationMesh Mesh(Window, M);

	while (Window->isOpen())
	{
		while (Window->pollEvent(E))
		{
			if(E.type == Event::Closed)
			{
				Window->close();
			}
		}

		P.Update(Window, M, GameTime::DeltaTime());

		Window->clear(Color::Cyan);
		
		M.DrawBackground(Window);
		P.Draw(Window);
		M.DrawProps(Window);
		
		Window->display();
		GameTime::Update();
	}

	return 0;
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest\doctest.h>
#endif // !Unittest