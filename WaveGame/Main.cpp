#include "GameTexture.h"
#include "Common.h"
#include "MapLoader.h"
#include "Player.h"
#include "GameTime.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include <SFML\Graphics.hpp>
#include <array>

using namespace sf;

#ifndef UNITTEST

int main(int argc, char** argv)
{
	srand(time(NULL));
	Engine::Core::InitTextureCache();
	RenderWindow* Window = new RenderWindow(VideoMode(800, 600, 32), "Game");
	Event E;
	
	shared_ptr<Engine::GamePlay::Player> P = make_shared<Engine::GamePlay::Player>();
	Engine::Core::Map M = Engine::Core::MapLoader::Load("Test.xml", Window);
	Engine::Core::CreateNavigationMesh(Window, *P, M);
	Engine::GamePlay::EnemyManager Enemies = Engine::GamePlay::EnemyManager(Window, P);

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

		Enemies.Update(Window, M, GameTime::DeltaTime());
		
		Window->clear(Color(0, 0, 0, 255));

		M.DrawBackground(Window);
		P->Draw(Window);
		M.DrawProps(Window);

		Enemies.Draw(Window);
		Engine::Core::DrawNavigationMesh(Window);

		Window->display();
		GameTime::Update();
	}

	delete Window;

	return 0;
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest\doctest.h>
#endif // !Unittest