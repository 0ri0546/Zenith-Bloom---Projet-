#pragma once

#include <queue>
#include "../systems/Node.hpp"
#include <unordered_map>
#include "../systems/grid.hpp"
#include "../map/Map.hpp"



class CompareNodePtr {
public : 
	bool operator()(const Node* a, const Node* b) const; 

};

struct Vector2iHash {

	std::size_t operator()(const sf::Vector2i& v) const; 

};


class Pathfinding {
	std::vector<sf::Vector2i> findPath(Grid& grid, sf::Vector2i start, sf::Vector2i end);
};