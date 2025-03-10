#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include "../systems/Datas.hpp"

class Platform {
public:
	Platform();
	Platform(float x, float y, float width, float height);
	sf::RectangleShape getShape() const;

private:
	sf::RectangleShape shape;
};

#endif