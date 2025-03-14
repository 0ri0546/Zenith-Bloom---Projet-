#include "Tiles.hpp"

Tiles::Tiles(float x, float y, int type)  : x(x), y(y), type(type){
	sprite.setTexture(Shared::floorTexture);
	switch (type)
	{
	case(00):
		sprite.setTextureRect(sf::IntRect(11*240, 0, 12*240, 240)); break;
	case(01):
		sprite.setTextureRect(sf::IntRect(0, 0, 240, 240)); break;
	case(02):
		sprite.setTextureRect(sf::IntRect(240, 0, 240, 240)); break;
	case(03):
		sprite.setTextureRect(sf::IntRect(480, 0, 240, 240)); break;
	case(04):
		sprite.setTextureRect(sf::IntRect(0, 240, 240, 240)); break;
	case(05):
		sprite.setTextureRect(sf::IntRect(240, 240, 240, 240)); break;
	case(06):
		sprite.setTextureRect(sf::IntRect(480, 240, 240, 240)); break;
	case(07):
		sprite.setTextureRect(sf::IntRect(0, 480, 240, 240)); break;
	case(8):
		sprite.setTextureRect(sf::IntRect(240, 480, 240, 240)); break;
	case(9):
		sprite.setTextureRect(sf::IntRect(480, 480, 240, 240)); break;
	default:
		break;
	}
	sprite.setScale(0.5, 0.5);
	sprite.setPosition(x, y);
}

Tiles::~Tiles() {}

sf::Vector2f Tiles::getPos() const { return sf::Vector2f(x, y); }

sf::Sprite Tiles::getSprite() const { return sprite; }

void Tiles::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}