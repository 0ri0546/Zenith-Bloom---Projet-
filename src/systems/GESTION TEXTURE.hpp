#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>

using namespace std;

class TextureManager {

private:

	map<string, sf::Texture> texturesList;

public:

	const sf::Texture& getTexture(const string& textureFilePath) {
		if (texturesList.find(textureFilePath) == texturesList.end()) {
			sf::Texture texture;
			if (!texture.loadFromFile(textureFilePath)) {
				std::cerr << "Erreur : Impossible de charger " << textureFilePath << std::endl;
			}
			texturesList[textureFilePath] = move(texture);
		}
		return texturesList[textureFilePath];
	}

};