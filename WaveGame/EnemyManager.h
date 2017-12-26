#pragma once

#include <memory>
#include <vector>
#include <iostream>
#include "stlastar.h"
#include "GameTexture.h"
#include "Character.h"
#include "Common.h"
#include "NavigationNode.h"
#include "Player.h"
#include "Map.h"
#include "GameTime.h"
#include "Enemy.h"

using namespace std;
using namespace sf;

#define DEFAULT_ENEMY_COUNT 5
#define INTERVAL_TIME 2.5f

namespace Engine::GamePlay
{
	enum MatchState
	{
		InMatch = 0,
		Interval,
		NewMatch
	};

	class EnemyManager
	{
	public:
		EnemyManager(RenderWindow* Window, shared_ptr<Player> P);
		~EnemyManager();

		void Update(RenderWindow* Window, Map M, float dt);
		void Draw(RenderWindow* Window);

	private:
		shared_ptr<Player> P;
		vector<Enemy> Enemies;
		int CurrentWave;
		int IntervalTimer;
		MatchState State;
	};
}

