#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <functional>

class Button {
private:
    int id;
    bool isSlider;
    bool isHovered;
    bool isDragging;

    std::string originalText;
    std::string name;
    int minValue, maxValue, initialValue;
    int currentValue;

    std::function<void()> onClick;
    sf::Font& font;
    sf::RectangleShape shape;
    sf::Text text;
    sf::RectangleShape bar;
    sf::CircleShape circle;
    sf::Text minText, maxText, valueText, nameText;

public:
    Button(int id, const std::string& label, const std::string& label2, sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> callback, int minValue = 0, int maxValue = 0, int initialValue = 0, bool slider = false);
    void handleMouseHover(const sf::Vector2i& mousePos);
    int handleInput(const sf::Vector2i& mousePos, const sf::Event& event, bool isController = false);
    void render(sf::RenderWindow& window);

    void setText(const std::string& label);
    void setHoverButton(const bool isHover);
    void setHoverSlider(const bool isHover);
    void adjustSliderValue(float axisValue);

    int getValue() const;
    std::string getOriginalText() const;
    bool getIsHovered() const;
    bool getIsSlider() const;
    int getId() const;
};

#endif // BUTTON_HPP