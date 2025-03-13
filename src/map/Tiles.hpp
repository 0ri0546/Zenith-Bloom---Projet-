#ifndef TILES_H
#define TILES_H


#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../systems/Datas.hpp"
#include "../systems/GESTION TEXTURE.hpp"
#include "../systems/AssetLoader.hpp"

class Tiles {
private:
	float x;
	float y;

	int type;
	sf::Sprite sprite;
public:
	Tiles(float x, float y, int type);
	~Tiles();
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPos();
	sf::Sprite getSprite();
};

#endif // !TILES_H

