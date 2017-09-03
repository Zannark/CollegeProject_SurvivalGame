#pragma once

#include <memory>
#include "SmartTexture.h"
#include "TextureCache.h"

using namespace std;

/// <summary>
/// Props are object in the maps environment.
/// </summary>
class Prop
{
public:
	Prop(string TextureID, string Tag = "");
	~Prop();

	void Draw(RenderWindow *Window);
	string GetTag();
private:
	SmartTexture Texture;
	string Tag;
};

