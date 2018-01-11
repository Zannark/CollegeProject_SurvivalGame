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
	srand((int)time(NULL));
	Engine::Core::InitTextureCache();
	RenderWindow* Window = new RenderWindow(VideoMode(800, 600, 32), "Game", Style::Close | Style::Titlebar);
	Event E;
	
	shared_ptr<Engine::GamePlay::Player> P = make_shared<Engine::GamePlay::Player>();
	Engine::Core::Map M = Engine::Core::MapLoader::Load("Test.xml", Window);
	Engine::Core::CreateNavigationMesh(Window, *P, M);
	Engine::GamePlay::EnemyManager* Enemies = new Engine::GamePlay::EnemyManager(Window, P);
	P->SetEnemyManager((void*)Enemies);

	Font EndGameFont;
	Text EndGameText;
	string EndGameMessage = "Game Over";
	
	EndGameFont.loadFromFile("Assets\\Heavy_Data.ttf");
	EndGameText.setFont(EndGameFont);
	EndGameText.setPosition(Vector2f((Window->getSize().x / 2) - EndGameText.getCharacterSize() * 2.5, (Window->getSize().y / 2) - EndGameText.getCharacterSize() * 2));
	EndGameText.setString(EndGameMessage);

	while (Window->isOpen())
	{
		while (Window->pollEvent(E))
		{
			if(E.type == Event::Closed)
			{
				Window->close();
			}
		}

		if (P->CheckHealth())
		{
			P->Update(Window, M, GameTime::DeltaTime());
			Enemies->Update(Window, M, GameTime::DeltaTime());
			Window->clear(Color(0, 0, 0, 255));

			M.DrawBackground(Window);
			P->DrawWeapon(Window);
			P->Draw(Window);
			M.DrawProps(Window);

			Enemies->Draw(Window);
			P->DrawUI(Window);
		}
		else
		{
			Window->clear(Color::Black);
			Window->draw(EndGameText);
		}

		Window->display();
		GameTime::Update();
	}

	delete Window;
	delete Enemies;

	return 0;
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest\doctest.h>
#endif // !Unittest