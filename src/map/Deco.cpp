#include "Deco.hpp"

Deco::Deco(float x, float y, int type) : x(x), y(y), type(type), fixed(false) {
    sprite.setTexture(Shared::propsTexture);

    sprite.setScale(0.5, 0.5);
    sprite.setPosition(x, y);
}


void Deco::setSprite(int type) {
    switch (type)
    {
    case(19):
        sprite.setTextureRect(sf::IntRect(0, 0, 480, 720)); break;
    case(20):
        sprite.setTextureRect(sf::IntRect(0, 0, 481, 720)); break;
    case(21):
        sprite.setTextureRect(sf::IntRect(0, 721, 481, 720)); break;
    case(22):
        sprite.setTextureRect(sf::IntRect(1480, 362, 2120 - 1480, 719 - 362)); break;
    case(23):
        sprite.setTextureRect(sf::IntRect(2200, 362, 2840 - 2200, 719 - 362)); break;
    case(24):
        sprite.setTextureRect(sf::IntRect(24, 1021, 716 - 24, 1440 - 1021)); break;
    case(25):
        sprite.setTextureRect(sf::IntRect(765, 1021, 1412 - 765, 1440 - 1021)); break;
    case(26):
        sprite.setTextureRect(sf::IntRect(37, 287, 2372 - 37, 1919 - 287)); break;
    case(27):
        sprite.setTextureRect(sf::IntRect((140 - 37) + 2545, 287, 4658 - (140 - 37) + 2545, 1919 - 287)); break;
    case(28):
        sprite.setTextureRect(sf::IntRect(87, 27, 1137 - 87, 1679 - 27)); break;
    case(29):
        sprite.setTextureRect(sf::IntRect(1286, 27, 2335 - 1286, 1679 - 27)); break;
    case(30):
        sprite.setTextureRect(sf::IntRect(326 - (1730 - 1472), 838, 1223 - 116, 477 - 838)); break;
    case(31):
        sprite.setTextureRect(sf::IntRect(1472, 838, 2780 - 1472, 477 - 838)); break;
    case(32):
        sprite.setTextureRect(sf::IntRect(1193, 167, 1584 - 1193, 1272 - 167)); break;
    case(33):
        sprite.setTextureRect(sf::IntRect(2113, 167, 2543 - 2113, 1272 - 167)); break;
    case(34):
        sprite.setTextureRect(sf::IntRect(28, 59, 1637 - 28, 1091 - 59)); break;
    case(35):
        sprite.setTextureRect(sf::IntRect(1708, 59, 0, 3317 - 1708 - 59)); break;
    case(36):
        sprite.setTextureRect(sf::IntRect(11, 0, 0, 0)); break;
    case(37):
        sprite.setTextureRect(sf::IntRect(21, 0, 0, 0)); break;
    default:
        return;
    }
}

sf::Sprite Deco::getSprite() const { return sprite; }
