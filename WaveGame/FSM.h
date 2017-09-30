#pragma once

#include <vector>
#include "Enemy.h"

using namespace std;

class FSM
{
public:
	FSM();
	~FSM();

	void Update(RenderWindow *Window, Player &P, float dt);
private:
	vector<Enemy> Enemies;
};

