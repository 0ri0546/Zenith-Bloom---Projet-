#ifndef REPARABLE_HPP
#define REPARABLE_HPP



#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../systems/Datas.hpp"
#include "../systems/GESTION TEXTURE.hpp"
#include "../systems/AssetLoader.hpp"

class Reparable
{
private:
	float x;
	float y;
	int size = 240;
	int type;
	bool shadow;
	bool empty;
	int value;
	bool isReparable;

	sf::Sprite sprite;

public:

	Reparable();
	~Reparable();


};

Reparable::Reparable()
{
}

Reparable::~Reparable()
{
}

#endif // !REPARABLE_HPP
