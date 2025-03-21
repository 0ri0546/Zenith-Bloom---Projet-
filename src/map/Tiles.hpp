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
	bool isShadow;
	bool empty;
	int value;
	bool isReparable;

	sf::Sprite sprite;
	sf::RectangleShape shadowShape;

public:
	Tiles(float x, float y, int type);
	~Tiles();

	void setSprite(int type);
	void setShadow(bool hasShadow);
	bool hasShadow() const;
	bool isEmpty() const;

	sf::Sprite getSprite() const;
	sf::Vector2f getPos() const;
	sf::RectangleShape getShadowShape() const;
	int getValue() const;
};

#endif 

