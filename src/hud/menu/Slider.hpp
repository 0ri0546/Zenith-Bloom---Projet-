#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Slider {
private:
    sf::RectangleShape bar;
    sf::CircleShape circle;
    sf::Text minText, maxText, valueText, nameText;
    sf::Font font;
    int minValue, maxValue, initialValue;
    int currentValue;
    bool isDragging;
    std::string name;

public:
    Slider(int x, int y, int width, int height, int minValue, int maxValue, const sf::Font& font, const std::string& name, int initialValue);

    void handleInput(const sf::RenderWindow& window, const sf::Event& event);
    void render(sf::RenderWindow& window);
    int getValue() const;
};

#endif // SLIDER_HPP