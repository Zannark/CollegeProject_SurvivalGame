#include "GameTime.h"

Clock GameTime::DeltaTimer = Clock();
float GameTime::CurrentDelta = 0.0f;
float GameTime::PreviousDelta = 0.0f;

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
/// <returns>The deltatime (in ms).</returns>
float GameTime::DeltaTime()
{
	if (PreviousDelta >= 1)
		return 1;
	if (PreviousDelta > 0.16)
		return 0.16;
	return PreviousDelta;
}

/// <summary>
/// Updates the delta timer.
/// </summary>
void GameTime::Update()
{
	Time Dt = DeltaTimer.getElapsedTime();
	PreviousDelta = CurrentDelta;
	CurrentDelta = Dt.asSeconds();
	DeltaTimer.restart();
}