#pragma once

#include <SFML\System.hpp>

using namespace sf;

/// <summary>
/// A class detailing information about the time which frames take to complete.
/// </summary>
class GameTime
{
public:
	static void Init();
	static float DeltaTime();
	static void Update();

private:
	static float CurrentDelta;
	static float PreviousDelta;
	static Clock DeltaTimer;
};

