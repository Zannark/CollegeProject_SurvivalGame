#include "GameTexture.h"

Engine::Core::Cache<Engine::Core::GameTexture> Engine::Core::TextureCache::Cache = Engine::Core::Cache<Engine::Core::GameTexture>();

Engine::Core::GameTexture::GameTexture(const string& Path)
{
	this->Tex = make_shared<Texture>();

	if (!this->Tex->loadFromFile(Path))
	{
		string ErrorMessage = string("Failed to load texture at location: ") + Path;
		throw runtime_error(ErrorMessage);
	}

	this->GameSprite = make_shared<Sprite>();
	this->GameSprite->setTexture(*this->Tex);
}

Engine::Core::GameTexture::GameTexture(const GameTexture& Tex)
{
	this->Tex = Tex.GetSFMLTexture();

	this->GameSprite = make_shared<Sprite>();
	this->GameSprite->setTexture(*this->Tex);
}

Engine::Core::GameTexture::GameTexture(Texture Tex)
{
	this->Tex = make_shared<Texture>(Tex);
	this->GameSprite = make_shared<Sprite>();
	this->GameSprite->setTexture(*this->Tex);
}

Engine::Core::GameTexture::~GameTexture()
{
}

///<summary>
///Gets the sf::Texture which is used by the object.
///</summary>
///<returns>The sf::Texture used.</returns>
shared_ptr<Texture> Engine::Core::GameTexture::GetSFMLTexture(void) const
{
	return this->Tex;
}

///<summary>
///Gets the sf::Sprite used by the object.
///</summary>
///<returns>A shared_ptr to the sf::sprite.</returns>
shared_ptr<Sprite> Engine::Core::GameTexture::GetSFMLSprite(void)
{
	return this->GameSprite;
}

///<summary>
///Sets the position of the sprite, in 2D space.
///</summary>
///<param name = "Position">The position to set the </param>
void Engine::Core::GameTexture::SetPosition(const Vector2f& Position)
{
	this->GameSprite->setPosition(Position);
}

///<summary>
///Sets the rotation of the texture.
///</summary>
///<param name = "Angle">The angle to set the player to.</param>
void Engine::Core::GameTexture::SetRotation(float Angle)
{
	this->GameSprite->setRotation(Angle);
}

///<summary>
///Sets the origin for rotating the texutre.
///</summary>
///<param name = "Position">The position, relative to the sprite, to rotate the texture by.</param>
void Engine::Core::GameTexture::SetOrigin(const Vector2f& Position)
{
	this->GameSprite->setOrigin(Position);
}

///<summary>
///Moves the texture a given amount of pixels across the screen.
///</summary>
///<param name = "Offset">The amount of pixels to move the texture by from its current position.</param>
void Engine::Core::GameTexture::Move(const Vector2f& Offset)
{
	this->GameSprite->move(Offset);
}

///<summary>
///Renders the texture to the screen.
///</summary>
///<param name = "RenderWindow">The window to draw to.</param>
///<exception cref = "std::runtime_error">Throws if RenderWindow is a nullptr.</exception>
void Engine::Core::GameTexture::Draw(RenderWindow* RenderWindow)
{
	if (!RenderWindow)
		throw runtime_error("The RenderWindow cannot be null (at Engine::Core::GameTexture).");

	RenderWindow->draw(*this->GameSprite);
}

Vector2f Engine::Core::GameTexture::GetPosition(void) const
{
	return this->GameSprite->getPosition();
}

Vector2f Engine::Core::GameTexture::GetSize(void) const
{
	return Vector2f(this->Tex->getSize());
}

///<summary>
///Initalise the TextureCache, loads in all of the GameTextures off of the storeage drive.
///</summary>
void Engine::Core::InitTextureCache()
{
	TextureCache::Cache.Add("Assets/Background.png", GameTexture("Assets/Background.png"));
	TextureCache::Cache.Add("Assets/Player.png", GameTexture("Assets/Player.png"));
	TextureCache::Cache.Add("Assets/TestBuilding.png", GameTexture("Assets/TestBuilding.png"));
	TextureCache::Cache.Add("Assets/Enemy.png", GameTexture("Assets/Enemy.png"));
	TextureCache::Cache.Add("Assets/PlayerWeapon.png", GameTexture("Assets/PlayerWeapon.png"));
	TextureCache::Cache.Add("Assets/SpeedPowerUp.png", GameTexture("Assets/SpeedPowerUp.png"));
	TextureCache::Cache.Add("Assets/DamagePowerUp.png", GameTexture("Assets/DamagePowerUp.png"));
}
