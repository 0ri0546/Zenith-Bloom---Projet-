#include "Slider.hpp"
#include <sstream>

Slider::Slider(int x, int y, int width, int minValue, int maxValue, const sf::Font& font, const std::string& name, int initialValue)
    : minValue(minValue), maxValue(maxValue), currentValue(initialValue), isDragging(false), name(name), initialValue(initialValue) {

    bar.setSize(sf::Vector2f(width, 5.f));
    bar.setPosition(x, y);
    bar.setFillColor(sf::Color(150, 150, 150));

    float circleX = static_cast<float>(x) + ((static_cast<float>(initialValue) - static_cast<float>(minValue)) / static_cast<float>(maxValue - minValue)) * static_cast<float>(width);

    circle.setRadius(10.f);
    circle.setFillColor(sf::Color(0, 255, 0));
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setPosition(circleX, y + bar.getSize().y / 2);

    this->font = font;

    minText.setFont(this->font);
    minText.setString(std::to_string(minValue));
    minText.setCharacterSize(20);
    minText.setFillColor(sf::Color::White);
    minText.setPosition(x - 40, y - 10);

    maxText.setFont(this->font);
    maxText.setString(std::to_string(maxValue));
    maxText.setCharacterSize(20);
    maxText.setFillColor(sf::Color::White);
    maxText.setPosition(x + width + 10, y - 10);

    valueText.setFont(this->font);
    valueText.setString(std::to_string(currentValue));
    valueText.setCharacterSize(30);
    valueText.setFillColor(sf::Color::White);
    valueText.setOutlineColor(sf::Color::Black);
    valueText.setPosition(x + width / 2.f + 20, y - 70);
    valueText.setOutlineThickness(1);

    nameText.setFont(this->font);
    nameText.setString(name);
    nameText.setCharacterSize(30);
    nameText.setFillColor(sf::Color::White);
    nameText.setOutlineColor(sf::Color::Black);
    nameText.setOutlineThickness(1);

    float totalWidth = nameText.getLocalBounds().width + valueText.getLocalBounds().width + 10;
    float startX = x + width / 2.f - totalWidth / 2.f;

    nameText.setPosition(startX, y - 40);
    valueText.setPosition(startX + nameText.getLocalBounds().width + 10, y - 40);
}


void Slider::handleInput(const sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (circle.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
            isDragging = true;
        }
    }

    if (event.type == sf::Event::MouseMoved && isDragging) {
        float mouseX = static_cast<float>(event.mouseMove.x);
        float newPosition = std::clamp(mouseX, bar.getPosition().x, bar.getPosition().x + bar.getSize().x);
        circle.setPosition(newPosition, circle.getPosition().y);

        float ratio = (newPosition - bar.getPosition().x) / bar.getSize().x;
        currentValue = minValue + ratio * (maxValue - minValue);
        valueText.setString(std::to_string(currentValue));
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        isDragging = false;
    }
}

void Slider::render(sf::RenderWindow& window) {
    window.draw(bar);
    window.draw(circle);
    window.draw(minText);
    window.draw(maxText);
    window.draw(valueText);
    window.draw(nameText);
}

int Slider::getValue() const {
    return currentValue;
}

void Slider::handleGamepadInput(float deltaX) {
    float currentPosition = circle.getPosition().x;
    float newPosition = std::clamp(currentPosition + deltaX, bar.getPosition().x, bar.getPosition().x + bar.getSize().x);

    circle.setPosition(newPosition, circle.getPosition().y);

    float ratio = (newPosition - bar.getPosition().x) / bar.getSize().x;
    currentValue = minValue + static_cast<int>(ratio * (maxValue - minValue));

    valueText.setString(std::to_string(currentValue));
}