#include "../systems/pathfinfing.hpp"

bool CompareNode::operator()(const Node* a, const Node* b) const
{

	return a->fCost > b->fCost;

}
	
std::size_t Vector2fHash::operator()(const sf::Vector2f& v) const
{
	return std::hash<float>()(v.x) ^ std::hash<float>()(v.y);
}
