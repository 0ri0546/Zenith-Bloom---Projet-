#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    int id;
    sf::RectangleShape shape;
    sf::Text text;
    std::function<void()> onClick;
    bool isHovered;

public:
    Button(int id, const std::string& label, sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> callback);
    void handleMouseHover(const sf::Vector2i& mousePos);
    int handleMouseClick(const sf::Vector2i& mousePos);
    void render(sf::RenderWindow& window);
};

#endif // BUTTON_HPP