#include "GameTexture.h"

Engine::Core::Cache<Engine::Core::GameTexture> Engine::Core::TextureCache::Cache = Engine::Core::Cache<Engine::Core::GameTexture>();

Engine::Core::GameTexture::GameTexture(const string& Path)
{
	if (!this->Tex.loadFromFile(Path))
	{
		string ErrorMessage = string("Failed to load texture at location: ") + Path;
		throw runtime_error(ErrorMessage);
	}

	this->GameSprite = make_shared<Sprite>();
	this->GameSprite->setTexture(this->Tex);
}

Engine::Core::GameTexture::GameTexture(const GameTexture& Tex)
{
	this->Tex = Tex.GetSFMLTexture();

	this->GameSprite = make_shared<Sprite>();
	this->GameSprite->setTexture(this->Tex);
}

Engine::Core::GameTexture::GameTexture(Texture Tex)
{
	this->Tex = Tex;
	this->GameSprite = make_shared<Sprite>();
	this->GameSprite->setTexture(this->Tex);
}

Engine::Core::GameTexture::~GameTexture()
{
}

Texture Engine::Core::GameTexture::GetSFMLTexture(void) const
{
	return this->Tex;
}

shared_ptr<Sprite> Engine::Core::GameTexture::GetSFMLSprite(void)
{
	return this->GameSprite;
}

void Engine::Core::GameTexture::SetPosition(Vector2f Position)
{
	this->GameSprite->setPosition(Position);
}

void Engine::Core::GameTexture::Draw(shared_ptr<RenderWindow> RenderWindow)
{
	if (!RenderWindow)
		throw runtime_error("The RenderWindow cannot be null (at Engine::Core::GameTexture).");

	RenderWindow->draw(*this->GameSprite);
}

void Engine::Core::InitTextureCache()
{
	TextureCache::Cache.Add("Assets/Background.png", GameTexture("Assets/Background.png"));
	TextureCache::Cache.Add("Assets/Tarn.png", GameTexture("Assets/Tarn.png"));
}
