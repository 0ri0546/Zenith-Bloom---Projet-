#include "AssetLoader.hpp"
#include "Datas.hpp"

#include <iostream>

Assets::Assets() {
	loadAssetsFromFiles();
}

void Assets::loadAssetsFromFiles() {
	if (!Shared::font.loadFromFile("")) // FONT
		std::cerr << "Chargement de la police impossible" << '\n';
	
	Shared::playerTexture.loadFromFile("assets/player/player.png");
	Shared::smokeTexture.loadFromFile("assets/player/smoke.png");
	Shared::swordTexture.loadFromFile("assets/player/sword.jpg");
	Shared::groundTexture.loadFromFile("assets/maps/tile test/bob.jpg");
	Shared::ennemyTexture.loadFromFile("assets/player/sword.jpg");
}


void Assets::resize(sf::Sprite& sprite, float scaleX, float scaleY) {
	float scaleFinaleX = scaleX / sprite.getGlobalBounds().width;
	float scaleFinaleY = scaleY / sprite.getGlobalBounds().height;
	sprite.setScale(scaleFinaleX, scaleFinaleY);
}