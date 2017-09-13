#include "GameTime.h"

Clock GameTime::DeltaTimer = Clock();
int GameTime::CurrentDelta = 0.0f;
int GameTime::PreviousDelta = 0.0f;

/// <summary>
/// Initalises the game timer.
/// </summary>
void GameTime::Init()
{
	CurrentDelta = 1;
	PreviousDelta = 1;
	DeltaTimer.restart();
}

/// <summary>
/// Gets the time that the previous frame took to complete.
/// </summary>
/// <retuns>The deltatime (in ms).</returns>
int GameTime::DeltaTime()
{
	if (PreviousDelta <= 1)
		return 1;
	return PreviousDelta;
}

/// <summary>
/// Updates the delta timer.
/// </summary>
void GameTime::Update()
{
	Time Dt = DeltaTimer.getElapsedTime();
	PreviousDelta = CurrentDelta;
	CurrentDelta = Dt.asMilliseconds();
	DeltaTimer.restart();
}