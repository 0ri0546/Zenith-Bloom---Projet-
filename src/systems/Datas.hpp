#ifndef DATAS_HPP
#define DATAS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <SFML/Window/Keyboard.hpp>

namespace Config {
	static int WINDOW_WIDTH = 1920; // 800
	static int WINDOW_HEIGHT = 1080; // 800
}

namespace Keybind {
	enum class Action {
		MoveRight,
		MoveLeft,
		Jump,
		VitalSeed,
		Repair
	};

	void setKey(Action action, sf::Keyboard::Key key);
	sf::Keyboard::Key getKey(Action action);
}

class Shared {
public:
	//font
	static sf::Font font;

	//assets joueur
	static sf::Texture playerTexture;
	static sf::Texture playerReverseTexture;
	static sf::Texture smokeTexture;
	static sf::Texture swordTexture;
	static sf::Texture projectileTexture;

	// assets ennemy
	static sf::Texture ennemyTexture;
	static sf::Texture ennemyTextureR;
	static sf::Texture tankTexture;	
	static sf::Texture tankTextureR;
	static sf::Texture droneTexture;
	static sf::Texture droneTextureR;
	static sf::Texture incendTexture;
	static sf::Texture incendTextureR;
	static sf::Texture projIcend;

	//assets map
	static sf::Texture groundTexture; 
	static sf::Texture floorTexture; 
	static sf::Texture itemsTexture;
	static sf::Texture capsuleHPTexture;
	static sf::Texture capsuleEnergyTexture;
	//static sf::Sprite groundSprite; 

	//HUD
	static sf::Texture dayTexture;
	static sf::Texture nightTexture;
	static sf::Texture lifeBarTexture;
	static sf::Texture lifeBar2Texture;
	static sf::Texture energyBarTexture;
	static sf::Texture progressBarTexture;

	//menus
	static sf::Texture backgroundTexture;
};

#endif