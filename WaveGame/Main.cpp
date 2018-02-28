#include "Common.h"
#include "MapLoader.h"
#include "Player.h"
#include "GameTime.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "PowerUpManager.h"
#include "Animator.h"
#include <SFML\Graphics.hpp>
#include <array>
#include <random>

using namespace sf;

#ifndef UNITTEST

///<summary>
///The entry point of the program.
///Where the games main loop is, used to create all of the classes.
///</summary>
int main(int argc, char** argv)
{
	srand((int)time(NULL));

	mt19937* Generator = new mt19937();

	Engine::Core::InitAnimatorCache();
	RenderWindow* Window = new RenderWindow(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "A Knights Final Night", Style::Close | Style::Titlebar);
	Event E;

	Player* P = new Engine::GamePlay::Player();
	Engine::Core::Map M = Engine::Core::MapLoader::Load("Test.xml", Window);
	Engine::Core::CreateNavigationMesh(Window, *P, M);
	Engine::GamePlay::EnemyManager* Enemies = new Engine::GamePlay::EnemyManager(Window, P, Generator);
	P->SetEnemyManager((void*)Enemies);

	Font EndGameFont;
	Text EndGameText;
	const string EndGameMessage = "Game Over";
	
	EndGameFont.loadFromFile("Assets\\Heavy_Data.ttf");
	EndGameText.setFont(EndGameFont);
	EndGameText.setPosition(Vector2f((Window->getSize().x / 2) - (float)EndGameText.getCharacterSize() * 2.5f, (Window->getSize().y / 2) - (float)EndGameText.getCharacterSize() * 2));
	EndGameText.setString(EndGameMessage);
	EndGameText.setFillColor(Color::White);

	PowerUpManager PowerUps;

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
			PowerUps.Update(P, GameTime::DeltaTime());
			Window->clear(Color(0, 0, 0, 255));

			M.DrawBackground(Window);
			P->DrawWeapon(Window);
			P->Draw(Window);
			M.DrawProps(Window);
			PowerUps.Draw(Window);
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
	delete Generator;

	return 0;
}
#else
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest\doctest.h>
#endif // !Unittest