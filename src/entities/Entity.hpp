#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../systems/Datas.hpp"
#include "../map/Tiles.hpp"
#include "../systems/AssetLoader.hpp"

class Entity {
public:
	virtual void update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime, bool isDay, bool isInTheSun) = 0;
};

#endif