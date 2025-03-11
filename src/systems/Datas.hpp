#ifndef DATAS_HPP
#define DATAS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

namespace Config {
	static int WINDOW_WIDTH = 1920; // 800
	static int WINDOW_HEIGHT = 1080; // 800
}

class Shared {
public:
	//font
	static sf::Font font;

	//assets joueur
	static sf::Texture playerTexture;
	

	static sf::Texture smokeTexture;
	

	static sf::Texture swordTexture;

	//assets map
	static sf::Texture groundTexture; 
	//static sf::Sprite groundSprite; 

};

#endif