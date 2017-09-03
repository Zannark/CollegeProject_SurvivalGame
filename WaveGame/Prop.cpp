#include "Prop.h"

/// <summary>
/// Loads in the texture.
/// </summary>
/// <param name = "TextureID">The ID of the texture which is to be loaded.</param>
Prop::Prop(string TextureID, string Tag)
{
	this->Texture = TextureCache::GetTexure(TextureID);
}

Prop::~Prop()
{
}

/// <summary>
/// Renders the texture to the screen.
/// </summary>
/// <param>A pointer to the window which is being rendered to.</param>
void Prop::Draw(RenderWindow* Window)
{
	this->Texture.Draw(Window);
}

string Prop::GetTag()
{
	return this->Tag;
}
