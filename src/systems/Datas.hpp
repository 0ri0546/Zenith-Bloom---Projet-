#ifndef DATAS_HPP
#define DATAS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace Config {
	const static int WINDOW_WIDTH = 1920; // 800
	const static int WINDOW_HEIGHT = 1080; // 800
}

class Shared {
public:
	//font
	static sf::Font font;

	//assets joueur
	static sf::Texture playerTexture;
	

	static sf::Texture smokeTexture;
	

	static sf::Texture swordTexture;

	static sf::Texture projectileTexture;

	// assets ennemy
	static sf::Texture ennemyTexture;

	//assets map
	static sf::Texture groundTexture; 
	//static sf::Sprite groundSprite; 

};

#endif