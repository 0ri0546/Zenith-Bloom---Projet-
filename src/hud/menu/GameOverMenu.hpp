#ifndef GAMEOVERMENU_HPP
#define GAMEOVERMENU_HPP

#include <SFML/Graphics.hpp>
#include "../../systems/Datas.hpp"

class GameOverMenu {
public:
    GameOverMenu();
    void render(sf::RenderWindow& window);
    bool handleInput();

private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text pressKeyText;
};

#endif // GAMEOVERMENU_HPP