#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <memory>

using namespace sf;
using namespace std;

/// <summary>
///	Defines both a sf::Texture and a sf::Sprite. 
/// Keeping them in the same location for convience and safety.
/// </summary>
struct SmartTexture
{
	SmartTexture() {}

	/// <summary>
	/// Constructs a Smart Texture from a path, relative to the executable.
	/// </summary>
	/// <param name="Path">The relative path to the texture file on disk.</param>
	SmartTexture(string Path)
	{
		this->Tex = make_shared<Texture>();
		this->Tex->loadFromFile(Path);
		
		if (!this->Tex)
			throw runtime_error("Failed to load the texture: " + Path);

		this->SmartSprite = Sprite();
		this->SmartSprite.setTexture(*this->Tex);
	}

	/// <summary>
	/// Constructs a Smart Texture from a copy of a sf::Texture.
	/// </summary>
	/// <param name="Tex">The sf::Texture to make a SmartTexture from.</Param>
	SmartTexture(Texture Tex)
	{
		this->SmartSprite = Sprite();
		this->SmartSprite.setTexture(Tex);
	}

	/// <summary>
	/// Renders the sf::Sprite to a window.
	/// </summary>
	/// <param name="Window">A pointer to the sf::RenderWindow which the sf::Sprite will be drawn to.</param>
	void Draw(RenderWindow *Window)
	{
		Window->draw(this->SmartSprite);
	}

	void SetPosition(Vector2f Position)
	{
		this->SmartSprite.setPosition(Position);
	}

	void Move(Vector2f Offset)
	{
		this->SmartSprite.move(Offset);
	}

	Vector2f GetPosition()
	{
		return this->SmartSprite.getPosition();
	}

	Vector2u GetDimensions()
	{
		return this->Tex->getSize();
	}

	shared_ptr<Texture> Tex;
	Sprite SmartSprite;
};