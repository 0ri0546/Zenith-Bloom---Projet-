#include "Button.hpp"

Button::Button(int id, const std::string& label, sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> callback) : id(id), onClick(callback), isHovered(false) {
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Transparent);
    shape.setOutlineThickness(0);

    text.setFont(font);
    text.setString(label);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(1);

    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(position.x + (size.x - textBounds.width) / 2.f, position.y + (size.y - textBounds.height) / 2.f - textBounds.top);
}

void Button::handleMouseHover(const sf::Vector2i& mousePos) {
    bool wasHovered = isHovered;
    isHovered = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

    if (isHovered && !wasHovered) {
        text.setFillColor(sf::Color(0, 255, 50));
    }
    else if (!isHovered && wasHovered) {
        text.setFillColor(sf::Color::White);
    }
}

int Button::handleMouseClick(const sf::Vector2i& mousePos) {
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
        onClick();
        text.setFillColor(sf::Color(150, 150, 150));
        return id;
    }
    return 0;
}

void Button::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}