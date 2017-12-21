#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include <exception>
#include <memory>
#include "Cache.h"

using namespace std;
using namespace sf;

namespace Engine::Core
{
	///<summary>
	///Wraps around the SFML texture and puts both sf::Texture and sf::Sprite into one object.
	///</summary>
	class GameTexture
	{
	public:
		GameTexture(const string& Path);
		GameTexture(const GameTexture& Tex);
		GameTexture(Texture Tex);
		GameTexture() = default;
		~GameTexture();

		shared_ptr<Texture> GetSFMLTexture(void) const;
		shared_ptr<Sprite> GetSFMLSprite(void);
		void SetPosition(const Vector2f& Position);
		void SetRotation(float Angle);
		void SetOrigin(const Vector2f& Position);
		void Move(const Vector2f& Offset);
		void Draw(shared_ptr<RenderWindow> RenderWindow);

	private:
		shared_ptr<Texture> Tex;
		shared_ptr<Sprite> GameSprite;
	};

	class TextureCache
	{
	public:
		static Cache<GameTexture> Cache;
	};
	extern void InitTextureCache();
}

