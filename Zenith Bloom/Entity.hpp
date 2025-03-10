#ifndef ENTITY_HPP
#define ENTITY_HPP
#pragma once

#include "Datas.hpp"
#include "Platform.hpp"
#include "AssetLoader.hpp"

class Entity {
public:
	virtual void update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view) = 0;
};

#endif
