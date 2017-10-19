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
	class GameTexture
	{
	public:
		GameTexture(const string& Path);
		GameTexture(const GameTexture& Tex);
		GameTexture(Texture Tex);
		GameTexture() = default;
		~GameTexture();

		///<summary>
		///Gets the sf::Texture which is used by the object.
		///</summary>
		///<returns>The sf::Texture used.</returns>
		Texture GetSFMLTexture(void) const;
		
		///<summary>
		///Gets the sf::Sprite used by the object.
		///</summary>
		///<returns>A shared_ptr to the sf::sprite.</returns>
		shared_ptr<Sprite> GetSFMLSprite(void);

		///<summary>
		///Sets the position of the sprite, in 2D space.
		///</summary>
		///<param name = "Position">The position to set the </param>
		void SetPosition(Vector2f Position);

		///<summary>
		///Renders the texture to the screen.
		///</summary>
		///<param name = "RenderWindow">The window to draw to.</param>
		///<exception cref = "std::runtime_error">Throws if RenderWindow is a nullptr.</exception>
		void Draw(shared_ptr<RenderWindow> RenderWindow);

	private:
		Texture Tex;
		shared_ptr<Sprite> GameSprite;
	};

	class TextureCache
	{
	public:
		static Cache<GameTexture> Cache;
	};
	extern void InitTextureCache();
}

