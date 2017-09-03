#include "GameTime.h"

Clock GameTime::DeltaTimer = Clock();
int GameTime::CurrentDelta = 0.0f;
int GameTime::PreviousDelta = 0.0f;

void GameTime::Init()
{
	CurrentDelta = 1;
	PreviousDelta = 1;
	DeltaTimer.restart();
}

int GameTime::DeltaTime()
{
	if (PreviousDelta <= 1)
		return 1;
	return PreviousDelta;
}

void GameTime::Update()
{
	Time Dt = DeltaTimer.getElapsedTime();
	PreviousDelta = CurrentDelta;
	CurrentDelta = Dt.asMilliseconds();
	DeltaTimer.restart();
}