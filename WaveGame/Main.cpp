#include "GameTexture.h"
#include "Common.h"
#include "MapLoader.h"
#include "Player.h"
#include "GameTime.h"
#include "Enemy.h"
#include <SFML\Graphics.hpp>
#include <array>

using namespace sf;

#ifndef UNITTEST

int main(int argc, char** argv)
{
	Engine::Core::InitTextureCache();
	shared_ptr<RenderWindow> Window = make_shared<RenderWindow>(VideoMode(800, 600, 32), "Game");
	Event E;
	
	shared_ptr<Engine::GamePlay::Player> P = make_shared<Engine::GamePlay::Player>();
	Engine::Core::Map M = Engine::Core::MapLoader::Load("Test.xml", Window);
	Engine::GamePlay::Enemy En = Engine::GamePlay::Enemy(Vector2f(224, 224), Window, P);

	Engine::Core::CreateNavigationMesh(Window, *P, M);
	while (Window->isOpen())
	{
		while (Window->pollEvent(E))
		{
			if(E.type == Event::Closed)
			{
				Window->close();
			}
		}

		P->Update(Window, M, GameTime::DeltaTime());

		En.Update(Window, M, GameTime::DeltaTime());
		
		Window->clear(Color::Cyan);
		
		M.DrawBackground(Window);
		P->Draw(Window);
		M.DrawProps(Window);

		En.Draw(Window);

		Window->display();
		GameTime::Update();
	}

	return 0;
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest\doctest.h>
#endif // !Unittest