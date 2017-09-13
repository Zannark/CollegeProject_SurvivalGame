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
	Prop(string TextureID, string Tag = "", bool IsStatic = true);
	~Prop();

	void Draw(RenderWindow *Window);
	
	///Getters.
	string GetTag();
	bool GetStatic();
	bool GetCollision();

	///Setters.
	void SetTag(string Tag);
	void SetStatic(bool Static);
	void SetCollision(bool Collision);
	void SetPosition(Vector2f Position);
	void SetAnimationDelay(float Delay);
private:
	SmartTexture STexture;
	string Tag;
	bool IsStatic;
	bool DoesCollision;
	float AnimationDelay;
};

