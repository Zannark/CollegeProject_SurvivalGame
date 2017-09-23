#include "Prop.h"

/// <summary>
/// Loads in the texture.
/// </summary>
/// <param name = "TextureID">The ID of the texture which is to be loaded.</param>
/// <param name = "Tag">The props tag.</param>
/// <param name = "IsStatic">True if the prop does not have an animation, false otherwise.</param>
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

/// <summary>
/// Gets the tag of the prop, used for finding objects in the map.
/// <summary>
/// <returns>The props tag</returns>
string Prop::GetTag()
{
	return this->Tag;
}

/// <summary>
/// Gets if the prop is animated or not.
/// </summary>
/// <returns>True if the prop does not have an animation, false otherwise.</returns>
bool Prop::GetStatic()
{
	return this->IsStatic;
}

/// <summary>
/// Gets if the prop does any collision.
/// </summary>
/// <returns>True if the prop carries out any collision, false otherwise.</returns>
bool Prop::GetCollision()
{
	return this->DoesCollision;
}

SmartTexture Prop::GetTexture()
{
	return this->STexture;
}

/// <summary>
/// Sets the props tag, usually only called when the prop is loaded in.
/// <summary>
/// <param name = "Tag">The tag which the prop needs to have.</param>
void Prop::SetTag(string Tag)
{
	this->Tag = Tag;
}

/// <summary>
/// Sets if the prop is animated or not, usually only called when the prop is loaded in.
/// </summary>
/// <param name = "Static">True if non animated, false otherwise.</param>
void Prop::SetStatic(bool Static)
{
	this->IsStatic = Static;
}

/// <summary>
/// Sets if the prop carries out collision or not, usually only called when the prop is loaded in.
/// </summary>
/// <param name = "Collision">True if collides, false otherwise.</param>
void Prop::SetCollision(bool Collision)
{
	this->DoesCollision = Collision;
}

/// <summary>
/// Sets the position of the prop.
/// </summary>
/// <param name = "Position">The location in the world where the prop is.</param>
void Prop::SetPosition(Vector2f Position)
{
	this->STexture.SetPosition(Position);
}

/// <summary>
/// Sets the amount of time each animation frame takes, usually only called when the prop is loaded in.
/// </summary>
/// <param name = "Delay">The amount of time, in seconds, each animation frame takes.</param>
void Prop::SetAnimationDelay(float Delay)
{
	this->AnimationDelay = Delay;
}
