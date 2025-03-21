#ifndef DECO_HPP
#define DECO_HPP



#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../systems/Datas.hpp"
#include "../systems/GESTION TEXTURE.hpp"
#include "../systems/AssetLoader.hpp"

class Deco
{
private:
	float x;
	float y;
	int size = 240;
	int type;
	bool fixed;
	sf::Sprite sprite;

public:

	Deco(float x, float y, int type);
	sf::Sprite getSprite() const;

	void setSprite(int type);


};

#endif // !DECO_HPP
