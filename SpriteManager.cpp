#include "SpriteManager.h"
#include "TextureManager.h"

unordered_map<string, sf::Sprite> SpriteManager::sprites;

void SpriteManager::LoadSprite(const char* fileName)
{
	sf::Sprite sprite(TextureManager::GetTexture(fileName));
	sprites[fileName] = sprite;
}

sf::Sprite& SpriteManager::GetSprite(const char* textKey)
{
	return sprites[textKey];
}

void SpriteManager::Clear()
{
	sprites.clear();
}