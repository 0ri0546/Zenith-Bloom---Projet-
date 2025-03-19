#include "AssetLoader.hpp"
#include "Datas.hpp"

#include <iostream>

Assets::Assets() {
	loadAssetsFromFiles();
}

void Assets::loadAssetsFromFiles() {
	if (!Shared::font.loadFromFile("assets/fonts/ethno.otf"))
		std::cerr << "Chargement de la police impossible" << '\n';
	
	Shared::playerTexture.loadFromFile("assets/player/player.png");
	Shared::playerReverseTexture.loadFromFile("assets/player/playerReverse.png");
	Shared::smokeTexture.loadFromFile("assets/player/smoke.png");
	Shared::swordTexture.loadFromFile("assets/player/sword.jpg");
	Shared::groundTexture.loadFromFile("assets/maps/tile test/bob.jpg");
	Shared::floorTexture.loadFromFile("assets/maps/tileset/tiles.png");

	Shared::ennemyTexture.loadFromFile("assets/ennemies/newTilsetEnemy.png");

	Shared::tankTexture.loadFromFile("assets/ennemies/retouche/tankTile.png");
	Shared::tankTextureR.loadFromFile("assets/ennemies/retouche/tankTileR.png");
	Shared::droneTexture.loadFromFile("assets/ennemies/droneTest.png");

	Shared::incendTextureR.loadFromFile("assets/ennemies/retouche/incendTile.png");
	Shared::incendTexture.loadFromFile("assets/ennemies/retouche/incendTileR.png");

	Shared::projectileTexture.loadFromFile("assets/player/projectilePlayer.png");
	Shared::dayTexture.loadFromFile("assets/player/sword.jpg");
	Shared::nightTexture.loadFromFile("assets/maps/tile test/bob.jpg");
	Shared::progressBarTexture.loadFromFile("assets/textures/hudTest.png");
	Shared::itemsTexture.loadFromFile("assets/map/items.png");
}

void Assets::resize(sf::Sprite& sprite, float scaleX, float scaleY) {
	float scaleFinaleX = scaleX / sprite.getGlobalBounds().width;
	float scaleFinaleY = scaleY / sprite.getGlobalBounds().height;
	sprite.setScale(scaleFinaleX, scaleFinaleY);
}