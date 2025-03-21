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
	bool fixed;
	sf::Sprite sprite;

public:

	Reparable(float x, float y, int type);
	~Reparable();
	void setSprite(int type);


};

Reparable::~Reparable()
{
}

#endif // !REPARABLE_HPP
