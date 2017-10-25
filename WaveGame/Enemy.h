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
		Enemy(shared_ptr<NavigationMesh> Mesh);
		~Enemy();

	private:
		shared_ptr<NavigationMesh> Mesh;
		shared_ptr<GameTexture> Texture;
	};
}