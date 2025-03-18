#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include "../../systems/Datas.hpp"

class GameOver {
public:
    GameOver();
    void render(sf::RenderWindow& window);
    bool handleInput();

private:
    sf::RectangleShape background;
    sf::Font font;
    sf::Text gameOverText;
    sf::Text pressKeyText;
};

#endif // GAMEOVER_HPP