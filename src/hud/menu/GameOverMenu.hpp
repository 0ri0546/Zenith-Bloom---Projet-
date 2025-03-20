#ifndef GAMEOVERMENU_HPP
#define GAMEOVERMENU_HPP

#include "../../systems/Datas.hpp"

class GameOverMenu {
public:
    // constructeur
    GameOverMenu();

    // void 
    void render(sf::RenderWindow& window);

    // bool
    bool handleInput();

private:
    sf::RectangleShape background;

    sf::Font font;

    sf::Text gameOverText, pressKeyText;
};

#endif