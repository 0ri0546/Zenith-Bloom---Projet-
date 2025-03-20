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
	Shared::floorTexture.loadFromFile("assets/maps/tileset/tiles.png");

	Shared::ennemyTexture.loadFromFile("assets/ennemies/retouche/ennemiTile2.png");
	Shared::ennemyTextureR.loadFromFile("assets/ennemies/retouche/ennemiTile2R.png");

	Shared::tankTexture.loadFromFile("assets/ennemies/retouche/tankTile.png");
	Shared::tankTextureR.loadFromFile("assets/ennemies/retouche/tankTileR.png");
	//Shared::droneTexture.loadFromFile("assets/ennemies/droneTest.png");

	Shared::incendTextureR.loadFromFile("assets/ennemies/retouche/incendTile.png");
	Shared::incendTexture.loadFromFile("assets/ennemies/retouche/incendTileR.png");
	Shared::projIcend.loadFromFile("assets/proj/feu.png");

	Shared::projectileTexture.loadFromFile("assets/player/projectilePlayer.png");

	Shared::dayTexture.loadFromFile("assets/textures/hud/day.png");
	Shared::nightTexture.loadFromFile("assets/textures/hud/night.png");
	Shared::energyBarTexture.loadFromFile("assets/textures/hud/energyBar.png");
	Shared::progressBarTexture.loadFromFile("assets/textures/hud/progressBar.png");

	Shared::lifeBarTexture.loadFromFile("assets/textures/hud/lifeBar.png");
	Shared::lifeBar2Texture.loadFromFile("assets/textures/hud/lifeBar2.png");
	Shared::itemsTexture.loadFromFile("assets/maps/tileset/items.png");
	Shared::backgroundTexture.loadFromFile("assets/textures/menu/background.jpg");
}

void Assets::resize(sf::Sprite& sprite, float scaleX, float scaleY) {
	float scaleFinaleX = scaleX / sprite.getGlobalBounds().width;
	float scaleFinaleY = scaleY / sprite.getGlobalBounds().height;
	sprite.setScale(scaleFinaleX, scaleFinaleY);
}