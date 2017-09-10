#pragma once

///Used to shorten the namespace that's being used.
#include <filesystem>
#include <iostream>

namespace FS = std::experimental::filesystem;

extern void WaitForAnyKeyAndExit(int ReturnCode = -1);