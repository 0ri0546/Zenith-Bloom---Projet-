#include "AssetLoader.hpp"
#include "Datas.hpp"

#include <iostream>

Assets::Assets() {
	loadAssetsFromFiles();
}

void Assets::loadAssetsFromFiles() {
	if (!Shared::font.loadFromFile("assets/fonts/arial.ttf")) // FONT
		std::cerr << "Chargement de la police impossible" << '\n';
	
	Shared::playerTexture.loadFromFile("assets/ennemies/ennemies.png"); //assets/player/player.png
	Shared::smokeTexture.loadFromFile("assets/player/smoke.png");
	Shared::swordTexture.loadFromFile("assets/player/sword.jpg");
	Shared::groundTexture.loadFromFile("assets/maps/tile test/bob.jpg");
	Shared::floorTexture.loadFromFile("assets/maps/tileset/tiles.png");
	Shared::ennemyTexture.loadFromFile("assets/ennemies/ennemies.png");
	Shared::tankTexture.loadFromFile("assets/textures/ennemy/canonTest.png");
	Shared::droneTexture.loadFromFile("assets/textures/ennemy/droneTest.png");
	Shared::incendTexture.loadFromFile("assets/textures/ennemy/incendTest.png");
	Shared::projectileTexture.loadFromFile("assets/player/sword.jpg");
	Shared::dayTexture.loadFromFile("assets/player/sword.jpg");
	Shared::nightTexture.loadFromFile("assets/maps/tile test/bob.jpg");
	Shared::progressBarTexture.loadFromFile("assets/textures/hudTest.png");
}

void Assets::resize(sf::Sprite& sprite, float scaleX, float scaleY) {
	float scaleFinaleX = scaleX / sprite.getGlobalBounds().width;
	float scaleFinaleY = scaleY / sprite.getGlobalBounds().height;
	sprite.setScale(scaleFinaleX, scaleFinaleY);
}