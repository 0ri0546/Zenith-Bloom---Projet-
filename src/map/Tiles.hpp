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
	int size = 240;
	int type;
	sf::Sprite sprite;
public:
	Tiles(float x, float y, int type);
	~Tiles();
	sf::Vector2f getPos() const ;
	sf::Sprite getSprite() const;

	bool isPolluted;
};

#endif // !TILES_H

