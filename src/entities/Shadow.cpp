#include "Shadow.hpp"

Shadow::Shadow(const sf::Vector2f& size, float x, float y) {
    setPosition(sf::Vector2f(x, y));
    setSize(size);
    updateShadowAppearance();
}

void Shadow::setPosition(const sf::Vector2f& position) {
    sf::RectangleShape::setPosition(position);
}

void Shadow::setSize(const sf::Vector2f& size) {
    sf::RectangleShape::setSize(size);
    updateShadowAppearance();
}

void Shadow::updateShadowAppearance() {
    setFillColor(sf::Color(0, 0, 0, 128));
}