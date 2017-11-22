#pragma once

#include <memory>
#include "NavigationMesh.h"
#include "GameTexture.h"
#include "Character.h"

using namespace Engine::Core;
using namespace std;

namespace Engine::GamePlay
{
	class Enemy : public Character
	{
	public:
		Enemy(shared_ptr<NavigationMesh> Mesh, Vector2f Position);
		~Enemy();

		void Update(shared_ptr<RenderWindow> Window, Map M, float dt);

	private:
		void CalculateNextNode();

		///The total amount of places moved at any one given time. 
		int CurrentTotalMoves;
		shared_ptr<NavigationMesh> Mesh;
		NavigationNode CurrentNode;
	};
}