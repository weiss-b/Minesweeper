#pragma once
#include "SFML/Graphics.hpp"
#include <unordered_map>
#include <string>
using std::unordered_map;
using std::string;

class TextureManager
{
	static unordered_map<string, sf::Texture> textures;

public:
	static void LoadTexture(const char* fileName);
	static sf::Texture& GetTexture(const char* textKey);
	static void Clear();
};

