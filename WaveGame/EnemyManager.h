#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include "stlastar.h"
#include "Animator.h"
#include "Character.h"
#include "Common.h"
#include "NavigationNode.h"
#include "Player.h"
#include "Map.h"
#include "GameTime.h"
#include "Enemy.h"
#include "SFML_Collision.h"

using namespace std;
using namespace sf;

#define DEFAULT_ENEMY_COUNT 5
#define INTERVAL_TIME 2.5f

namespace Engine::GamePlay
{
	///<summary>
	///The different states that the round can be in.
	///</summary>
	enum MatchState
	{
		InMatch = 0,
		Interval,
		NewMatch
	};

	///<summary>
	///The object which is resposible for controlling all of the enemies in the game.
	///</summary>
	class EnemyManager
	{
	public:
		EnemyManager(RenderWindow* Window, Player* P, mt19937* Generator);
		~EnemyManager();

		void Update(RenderWindow* Window, Map M, float dt);
		void Draw(RenderWindow* Window);

		vector<Enemy*> GetEnemiesInRange();

	private:
		Player* P;
		vector<Enemy*> Enemies;
		int CurrentWave;
		float IntervalTimer;
		MatchState State;
		int RoundNumber;
		string RoundMessage;
		Font RoundFont;
		Text RoundText;
		uniform_real_distribution<float> RandomNumber;
		mt19937* Generator;
	};
}

