#include "Enemy.h"

void PrintEnemyStates(EnemyStates State, bool Endl)
{
	switch (State)
	{
	case EnemyStates::STATE_IDLE:
		cout << "EnemyState::STATE_IDLE";
		break;

	case EnemyStates::STATE_ATTACK:
		cout << "EnemyState::STATE_ATTACK";
		break;

	case EnemyStates::STATE_RANGE_CHECK:
		cout << "EnemyState::STATE_RANGE_CHECK";
		break;

	case EnemyStates::STATE_MOVING_TOWARDS_PLAYER:
		cout << "EnemyState::STATE_MOVING_TOWARDS_PLAYER";
		break;
	}

	if (Endl)
		cout << endl;
}

void PrintEnemyInfo(Enemy E)
{
	cout << "Enemy: " << E.GetID() << " is in current state ";
	PrintEnemyStates(E.GetState(), true);
}

Enemy::Enemy()
{
	this->ID = ++CommonData::CurrentID;
	this->State = EnemyStates::STATE_IDLE;
}

Enemy::~Enemy()
{
}

void Enemy::SetState(EnemyStates State)
{
	this->State = State;
}

void Enemy::Update(RenderWindow *Window, Player &P, float dt)
{
	switch (this->State)
	{
	case EnemyStates::STATE_IDLE:
		break;

	case EnemyStates::STATE_RANGE_CHECK:
		this->UpdateRange(Window, P, dt);
		break;

	case EnemyStates::STATE_ATTACK:
		this->UpdateAttack(Window, P, dt);
		break;

	case EnemyStates::STATE_MOVING_TOWARDS_PLAYER:
		this->UpdateMoveToPlayer(Window, P, dt);
	}
}

int Enemy::GetID(void)
{
	return this->ID;
}

EnemyStates Enemy::GetState()
{
	return this->State;
}

void Enemy::UpdateRange(RenderWindow *Window, Player &P, float dt)
{

}

void Enemy::UpdateAttack(RenderWindow *Window, Player &P, float dt)
{

}

void Enemy::UpdateMoveToPlayer(RenderWindow * Window, Player & P, float dt)
{

}
