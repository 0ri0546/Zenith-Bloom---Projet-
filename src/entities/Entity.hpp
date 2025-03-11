#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../systems/Datas.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include <cmath> 

class Entity {
public:
	virtual void update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view, float deltaTime) = 0;
};

#endif