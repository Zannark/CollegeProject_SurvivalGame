#pragma once

#include <memory>
#include <math.h>
#include "Enemy.h"
#include "Player.h"
#include "NavigationMesh.h"
#include "Common.h"

using namespace std;
using namespace Engine::Misc;
using namespace Engine::Core;
using namespace Engine::GamePlay;

namespace Engine::Core
{
	class PathFinding
	{
	public:
		PathFinding();
		~PathFinding();

	private:
		///<summary>
		///Calculates the euclidean distance from the enemy to the player.
		///</summary>
		///<param name = "Plr">The player.</param>
		///<param name = "Enemy">The enemy.</param>
		void CalculateEstimateDistance(Player Plr, Enemy Enemy);
	
		///<summary>
		///The estimated distance to the player.
		///</summary>
		float EstimatedDistance;
	};
}