#ifndef DATAS_HPP
#define DATAS_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

const static int WIDTH = 800;
const static int HEIGHT = 800;

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