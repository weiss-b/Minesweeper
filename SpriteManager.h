#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class SpriteManager
{
	static unordered_map<string, sf::Sprite> sprites;

public:
	static void LoadSprite(const char* fileName);
	static sf::Sprite& GetSprite(const char* textKey);
	static void Clear();
};



