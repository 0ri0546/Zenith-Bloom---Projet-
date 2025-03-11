#pragma once

#include <queue>
#include "../systems/Node.hpp"
#include <unordered_map>


class CompareNode {
public : 
	bool operator()(const Node* a, const Node* b) const; 

};

struct Vector2fHash {

	std::size_t operator()(const sf::Vector2f& v) const; 

};

//std::vector<sf::Vector2f> findPath(grid& grid, sf::Vector2f start, sf::Vector2i end); 