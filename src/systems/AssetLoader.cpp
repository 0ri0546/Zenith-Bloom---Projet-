#include "AssetLoader.hpp"
#include "Datas.hpp"

#include <iostream>

Assets::Assets() {
	loadAssetsFromFiles();
}

void Assets::loadAssetsFromFiles() {
	if (!Shared::font.loadFromFile("assets/fonts/ethno.otf"))
		std::cerr << "Chargement de la police impossible" << '\n';
	
	// player
	Shared::playerTexture.loadFromFile("assets/player/player.png");
	Shared::playerReverseTexture.loadFromFile("assets/player/playerReverse.png");
	Shared::smokeTexture.loadFromFile("assets/player/smoke.png");
	Shared::swordTexture.loadFromFile("assets/player/sword.jpg");
	Shared::projectileTexture.loadFromFile("assets/player/projectilePlayer.png");
	Shared::waterProjTexture.loadFromFile("assets/player/water.png");

	// map
	Shared::floorTexture.loadFromFile("assets/maps/tileset/tiles.png");
	Shared::propsTexture.loadFromFile("assets/maps/tileset/props.png");
	Shared::boxTexture.loadFromFile("assets/maps/reparable/solarebirth_panneau_recyclage_bac.png");
	Shared::serreTexture.loadFromFile("assets/maps/reparable/solarebirth_serre.png");
	Shared::antenneTexture.loadFromFile("assets/maps/reparable/solarrebirth_antenne.png");
	Shared::carTexture.loadFromFile("assets/maps/reparable/solarrebirth_car.png");
	Shared::eolienneTexture.loadFromFile("assets/maps/reparable/solarrebirth_eolienne.png");
	Shared::lampadaireTexture.loadFromFile("assets/maps/reparable/solarrebirth_lampadaire.png");
	Shared::panneauTexture.loadFromFile("assets/maps/reparable/solarrebirth_solaire.png");

	// ennemies
	Shared::ennemyTexture.loadFromFile("assets/ennemies/retouche/ennemiTile2.png");
	Shared::droneTexture.loadFromFile("assets/ennemies/drone.png");
	Shared::ennemyTextureR.loadFromFile("assets/ennemies/retouche/ennemiTile2R.png");
	Shared::projMini.loadFromFile("assets/proj/missile.png");
	Shared::tankTexture.loadFromFile("assets/ennemies/retouche/tankTile.png");
	Shared::tankTextureR.loadFromFile("assets/ennemies/retouche/tankTileR.png");
	Shared::incendTextureR.loadFromFile("assets/ennemies/retouche/incendTile.png");
	Shared::incendTexture.loadFromFile("assets/ennemies/retouche/incendTileR.png");
	Shared::projIcend.loadFromFile("assets/proj/feu.png");
	Shared::flame.loadFromFile("assets/flame.png");

	// HUD
	Shared::dayTexture.loadFromFile("assets/textures/hud/day.png");
	Shared::nightTexture.loadFromFile("assets/textures/hud/night.png");
	Shared::energyBarTexture.loadFromFile("assets/textures/hud/energyBar.png");
	Shared::progressBarTexture.loadFromFile("assets/textures/hud/progressBar.png");
	Shared::lifeBar2Texture.loadFromFile("assets/textures/hud/lifeBar2.png");
	Shared::backgroundTexture.loadFromFile("assets/textures/menu/background.jpg");
	Shared::capsuleHPTexture.loadFromFile("assets/maps/tileset/capsule_hp.png");
	Shared::capsuleEnergyTexture.loadFromFile("assets/maps/tileset/capsule_energie.png");
	Shared::surchauffeBarTexture.loadFromFile("assets/textures/hud/surchauffeBar.png");

}

void Assets::resize(sf::Sprite& sprite, float scaleX, float scaleY) {
	float scaleFinaleX = scaleX / sprite.getGlobalBounds().width;
	float scaleFinaleY = scaleY / sprite.getGlobalBounds().height;
	sprite.setScale(scaleFinaleX, scaleFinaleY);
}