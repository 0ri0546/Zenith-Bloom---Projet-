#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../systems/Datas.hpp"
#include "../map/Tiles.hpp"
#include "../systems/AssetLoader.hpp"
#include <cmath> 

class Entity {
public:
	virtual void update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime, bool isDay) = 0;
};

#endif