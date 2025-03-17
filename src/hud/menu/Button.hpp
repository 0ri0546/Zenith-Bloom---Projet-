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
    std::string originalText;

    bool isSlider;
    sf::RectangleShape bar;
    sf::CircleShape circle;
    sf::Text minText, maxText, valueText, nameText;
    sf::Font& font;
    int minValue, maxValue, initialValue;
    int currentValue;
    bool isDragging;
    std::string name;

public:
    Button(int id, const std::string& label, const std::string& label2, sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> callback, int minValue = 0, int maxValue = 0, int initialValue = 0, bool slider = false);
    void handleMouseHover(const sf::Vector2i& mousePos);
    int handleInput(const sf::Vector2i& mousePos, const sf::Event& event, bool isController = false);
    void render(sf::RenderWindow& window);

    void setText(const std::string& label);
    void setHoverButton(const bool isHover);
    int getValue() const;
    void setHoverSlider(const bool isHover);

    std::string getOriginalText() const {
        return originalText;
    }

    bool getIsHovered() const {
        return isHovered;
    }

    bool getIsSlider() const {
        return isSlider;
    }
};

#endif // BUTTON_HPP