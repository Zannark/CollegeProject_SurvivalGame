#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include <stdexcept>
#include "SmartTexture.h"

using namespace sf;
using namespace std;

class TextureCache
{
public:
	static void Init();

	static SmartTexture GetTexure(string ID);
private:
	static map<string, SmartTexture> Textures;
};

