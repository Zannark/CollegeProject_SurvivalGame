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
	//Engine::GamePlay::Enemy En = Engine::GamePlay::Enemy(Vector2f(0, 0), Window, P);

	Engine::Core::CreateNavigationMesh(Window, *P, M);

	Enemy e1 = Enemy(Vector2f(0, 0), Window, P);
	Enemy e2 = Enemy(Vector2f(32, 0), Window, P);
	Enemy e3 = Enemy(Vector2f(64, 0), Window, P);
	Enemy e4 = Enemy(Vector2f(96, 0), Window, P);
	Enemy e5 = Enemy(Vector2f(128, 0), Window, P);
	Enemy e6 = Enemy(Vector2f(160, 0), Window, P);
	Enemy e7 = Enemy(Vector2f(192, 0), Window, P);
	Enemy e8 = Enemy(Vector2f(200, 0), Window, P);

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
		//En.Update(Window, M, GameTime::DeltaTime());
		// Why does it randomly corrupt itself

		e1.Update(Window, M, GameTime::DeltaTime());
		e2.Update(Window, M, GameTime::DeltaTime());
		e3.Update(Window, M, GameTime::DeltaTime());
		e4.Update(Window, M, GameTime::DeltaTime());
		e5.Update(Window, M, GameTime::DeltaTime());
		e6.Update(Window, M, GameTime::DeltaTime());
		e7.Update(Window, M, GameTime::DeltaTime());
		e8.Update(Window, M, GameTime::DeltaTime());
		
		Window->clear(Color::Cyan);
		
		M.DrawBackground(Window);
		P->Draw(Window);
		M.DrawProps(Window);
		//En.Draw(Window);

		e1.Draw(Window);
		e2.Draw(Window);
		e3.Draw(Window);
		e4.Draw(Window);
		e5.Draw(Window);
		e6.Draw(Window);
		e7.Draw(Window);
		e8.Draw(Window);

		Window->display();
		GameTime::Update();
	}

	return 0;
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest\doctest.h>
#endif // !Unittest