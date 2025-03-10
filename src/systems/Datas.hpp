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
	static sf::Sprite playerSprite;

	static sf::Texture smokeTexture;
	static sf::Sprite smokeSprite;

	static sf::Texture swordTexture;
	static sf::Sprite swordSprite;

};

#endif