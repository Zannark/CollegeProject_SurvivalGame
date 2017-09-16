#include "TextureCache.h"

map<string, SmartTexture> TextureCache::Textures = map<string, SmartTexture>();

/// <summary>
/// Loads in all the textures for the in game objects at load time.
/// </summary>
void TextureCache::Init()
{
	const string AssetPath = "Assets/";

	Textures["Test"] = SmartTexture(AssetPath + "TestSquare.png");
	Textures["DefaultBackground"] = SmartTexture(AssetPath + "Test.png");
	Textures["DefaultPlayer"] = SmartTexture(AssetPath + "Tarn.png");
}

/// <summary>
/// Gets a texture from the map TextureCache::Textures by use of the ID.
/// If the Texture does not exsist then a std::runtime_error is thrown.
/// </summary>
/// <param name="ID">The ID of the texture which is to be accessed.</param>
/// <returns>A shared pointer to the texture.</returns>
SmartTexture TextureCache::GetTexure(string ID)
{
	if (Textures.find(ID) == Textures.end())
		throw runtime_error(string("Failed to find texture with ID: ") + ID);

	return Textures[ID];
}
