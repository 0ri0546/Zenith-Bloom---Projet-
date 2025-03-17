#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "../../systems/Datas.hpp"
#include <cmath>

class Menu {
protected:
    sf::Font font;
    std::vector<Button> buttons;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    virtual void initButtons() = 0;
    void initFont();
    void initBackground();

    void updateHoverForButton(int index);

    int currentHoveredButtonIndex = 0;
    bool isGamepadConnected = false;
    void updateHoverWithGamepad();

public:
    Menu();
    virtual ~Menu() = default;
    virtual int handleInput(sf::RenderWindow& window, const sf::Event& event);
    virtual void render(sf::RenderWindow& window);
};

#endif // MENU_HPP