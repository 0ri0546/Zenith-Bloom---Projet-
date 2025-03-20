#include "Button.hpp"
#include <iostream>

Button::Button(int id, const std::string& label, const std::string& label2, sf::Font& font, sf::Vector2f position, sf::Vector2f size, std::function<void()> callback, int minValue, int maxValue, int initialValue, bool slider)
    : id(id), name(label), originalText(label2), font(font), onClick(callback), isSlider(slider), minValue(minValue), maxValue(maxValue), initialValue(initialValue), currentValue(initialValue), isHovered(false), isDragging(false) {

    if (slider) {
        bar.setSize(size);
        bar.setPosition(position);
        bar.setFillColor(sf::Color(150, 150, 150));

        float circleX = static_cast<float>(position.x) + ((static_cast<float>(initialValue) - static_cast<float>(minValue)) / static_cast<float>(maxValue - minValue)) * static_cast<float>(size.x);

        circle.setRadius(10.f);
        circle.setFillColor(sf::Color(0, 255, 0));
        circle.setOrigin(circle.getRadius(), circle.getRadius());
        circle.setPosition(circleX, position.y + bar.getSize().y / 2);


        minText.setFont(font);
        minText.setString(std::to_string(minValue));
        minText.setCharacterSize(20);
        minText.setFillColor(sf::Color::White);
        minText.setPosition(position.x - 40, position.y - 10);

        maxText.setFont(font);
        maxText.setString(std::to_string(maxValue));
        maxText.setCharacterSize(20);
        maxText.setFillColor(sf::Color::White);
        maxText.setPosition(position.x + size.x + 10, position.y - 10);

        valueText.setFont(font);
        valueText.setString(std::to_string(currentValue));
        valueText.setCharacterSize(30);
        valueText.setFillColor(sf::Color::White);
        valueText.setOutlineColor(sf::Color::Black);
        valueText.setPosition(position.x + size.x / 2.f + 20, position.y - 70);
        valueText.setOutlineThickness(1);

        nameText.setFont(font);
        nameText.setString(name);
        nameText.setCharacterSize(30);
        nameText.setFillColor(sf::Color::White);
        nameText.setOutlineColor(sf::Color::Black);
        nameText.setOutlineThickness(1);

        float totalWidth = nameText.getLocalBounds().width + valueText.getLocalBounds().width + 10;
        float startX = position.x + size.x / 2.f - totalWidth / 2.f;

        nameText.setPosition(startX, position.y - 40);
        valueText.setPosition(startX + nameText.getLocalBounds().width + 10, position.y - 40);
    }

    else {
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
}

void Button::handleMouseHover(const sf::Vector2i& mousePos) {
    if (isSlider) {
        bool wasHovered = isHovered;
        isHovered = circle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

        if (isHovered && !wasHovered) {
            valueText.setFillColor(sf::Color(0, 255, 50));
            nameText.setFillColor(sf::Color(0, 255, 50));
        }
        else if (!isHovered && wasHovered) {
            valueText.setFillColor(sf::Color::White);
            nameText.setFillColor(sf::Color::White);
        }
    }

    else {
        bool wasHovered = isHovered;
        isHovered = shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));

        if (isHovered && !wasHovered) {
            text.setFillColor(sf::Color(0, 255, 50));
        }
        else if (!isHovered && wasHovered) {
            text.setFillColor(sf::Color::White);
        }
    }
}

int Button::handleInput(const sf::Vector2i& mousePos, const sf::Event& event, bool isController) {
    if (isSlider) {
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

        if (isDragging || event.type == sf::Event::MouseButtonPressed) {
            return id;
        }
    }
    else {
        if (isController || shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            onClick();
            return id;
        }
    }

    return 0;
}

void Button::render(sf::RenderWindow& window) {
    if (isSlider) {
        window.draw(bar);
        window.draw(circle);
        window.draw(minText);
        window.draw(maxText);
        window.draw(valueText);
        window.draw(nameText);
    }
    else {
        window.draw(shape);
        window.draw(text);
    }
}

void Button::setText(const std::string& label) {
    text.setString(label);
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setPosition(shape.getPosition().x + (shape.getSize().x - textBounds.width) / 2.f, shape.getPosition().y + (shape.getSize().y - textBounds.height) / 2.f - textBounds.top);
}

void Button::setHoverButton(const bool isHover) {
    if (isHover) {
        text.setFillColor(sf::Color(0, 255, 50));
    }
    else {
        text.setFillColor(sf::Color::White);
    }
}

void Button::setHoverSlider(const bool isHover) {
    if (isHover) {
        valueText.setFillColor(sf::Color(0, 255, 50));
        nameText.setFillColor(sf::Color(0, 255, 50));
    }
    else if (!isHover) {
        valueText.setFillColor(sf::Color::White);
        nameText.setFillColor(sf::Color::White);
    }
}

void Button::adjustSliderValue(float axisValue) {
    if (axisValue > 20) {
        currentValue = std::min(currentValue + 1, maxValue);
    }
    else if (axisValue < -20) {
        currentValue = std::max(currentValue - 1, minValue);
    }

    float newPositionX = bar.getPosition().x + (static_cast<float>(currentValue - minValue) / (maxValue - minValue)) * bar.getSize().x;
    circle.setPosition(newPositionX, circle.getPosition().y);
    valueText.setString(std::to_string(currentValue));
}

int Button::getValue() const {
    return currentValue;
}

std::string Button::getOriginalText() const {
    return originalText;
}

bool Button::getIsHovered() const {
    return isHovered;
}

bool Button::getIsSlider() const {
    return isSlider;
}

int Button::getId() const {
    return id;
}