#pragma once

///Used to shorten the namespace that's being used.
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>
#include <SFML\Graphics.hpp>
#include "Unittest.h"

#define PI 3.141592653

namespace FS = std::experimental::filesystem;

extern void WaitForAnyKeyAndExit(int ReturnCode = EXIT_FAILURE);
extern bool StringToBool(std::string Str);
extern std::string ToUpper(std::string Str);
extern std::string ToLower(std::string Str);
extern double ToRadians(double Degrees);
extern double ToDegrees(double Radians);