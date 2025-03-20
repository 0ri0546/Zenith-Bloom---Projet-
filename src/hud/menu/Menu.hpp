#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "../../systems/Datas.hpp"
#include <cmath>

class Menu {
protected:
    std::vector<Button> buttons;

    sf::Sprite backgroundSprite;

    virtual void initButtons() = 0;
    void initBackground();

    void updateHoverForButton(int index);
    void updateHoverWithGamepad();

    int currentHoveredButtonIndex = 0;
    bool isGamepadConnected = false;

public:
    Menu();
    virtual ~Menu() = default;
    virtual int handleInput(sf::RenderWindow& window, const sf::Event& event);
    virtual void render(sf::RenderWindow& window);
};

#endif