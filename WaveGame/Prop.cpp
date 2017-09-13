#include "Prop.h"

/// <summary>
/// Loads in the texture.
/// </summary>
/// <param name = "TextureID">The ID of the texture which is to be loaded.</param>
Prop::Prop(string TextureID, string Tag, bool IsStatic)
{
	this->STexture = TextureCache::GetTexure(TextureID);
	this->Tag = Tag;
	this->IsStatic = IsStatic;
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
	this->STexture.Draw(Window);
}

string Prop::GetTag()
{
	return this->Tag;
}

bool Prop::GetStatic()
{
	return this->IsStatic;
}

bool Prop::GetCollision()
{
	return false;
}

void Prop::SetTag(string Tag)
{
	this->Tag = Tag;
}

void Prop::SetStatic(bool Static)
{
	this->IsStatic = Static;
}

void Prop::SetCollision(bool Collision)
{
	this->DoesCollision = Collision;
}

void Prop::SetPosition(Vector2f Position)
{
	this->STexture.SetPosition(Position);
}

void Prop::SetAnimationDelay(float Delay)
{
	this->AnimationDelay = Delay;
}
