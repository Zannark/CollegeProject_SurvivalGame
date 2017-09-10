#pragma once

///Used to shorten the namespace that's being used.
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <string>

namespace FS = std::experimental::filesystem;

extern void WaitForAnyKeyAndExit(int ReturnCode = -1);
extern bool StringToBool(std::string Bool);
extern std::string ToUpper(std::string Str);
extern std::string ToLower(std::string Str);