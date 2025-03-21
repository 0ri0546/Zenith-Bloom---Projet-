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

	sf::Sprite sprite;

public:
	bool fixed;
	Reparable(float x, float y, int type);
	sf::Sprite getSprite() const;

	void setSprite(int type);
	void fixing();

};



#endif // !REPARABLE_HPP
