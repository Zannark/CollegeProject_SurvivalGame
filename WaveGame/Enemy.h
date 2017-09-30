#pragma once

#include <ctime>
#include <SFML\Graphics.hpp>
#include "Character.h"
#include "Player.h"

using namespace sf;

/// <summary>
/// Defines all of the states for the enemy.
/// </summary>
enum class EnemyStates
{
	/// <summary>
	/// What the enemy does to begin with, when it first spawns in.
	/// </summary>
	STATE_IDLE = 0,

	/// <summary>
	/// What the enemy does as it walks to the player.
	/// </summary>
	STATE_MOVING_TOWARDS_PLAYER,

	/// <summary>
	///	The second thing the enemy does.
	/// This is what is done, while the enemy checks the distance between itself and the player.
	/// Takes place every three frames.
	/// </summary>
	STATE_RANGE_CHECK,

	/// <summary>
	///	The state when the player attacks.
	/// </summary>
	STATE_ATTACK
};

class Enemy : public Character
{
public:
	Enemy();
	~Enemy();

	void SetState(EnemyStates State);
	
	void Update(RenderWindow *Window, Player &P, float dt);

	int GetID(void);
	EnemyStates GetState();
private:
	int ID;
	EnemyStates State;

	void UpdateRange(RenderWindow *Window, Player &P, float dt);
	void UpdateAttack(RenderWindow *Window, Player &P, float dt);
	void UpdateMoveToPlayer(RenderWindow *Window, Player &P, float dt);
};

