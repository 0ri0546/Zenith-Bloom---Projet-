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

	sf::RectangleShape shadowShape;
	bool shadow;
	bool empty;
	int value;

public:
	Tiles(float x, float y, int type);
	~Tiles();
	sf::Vector2f getPos() const ;
	sf::Sprite getSprite() const;
	void setShadow(bool hasShadow);
	bool hasShadow() const;
	bool isEmpty() const;
	sf::RectangleShape getShadowShape() const;

	int getValue() const;


	bool isReparable;
};

#endif 

