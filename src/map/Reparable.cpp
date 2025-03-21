#include "Reparable.hpp"

Reparable::Reparable(float x, float y, int type) : x(x), y(y), type(type), fixed(false) {
    setSprite(type);
	sprite.setPosition(x, y);

}


void Reparable::setSprite(int type) {
    switch (type)
    {
    case(00):
        sprite.setTextureRect(sf::IntRect(0,0 ,480 ,720)); break;
    case(01):
        sprite.setTexture(Shared::boxTexture);
        sprite.setTextureRect(sf::IntRect(0, 0 , 481, 720)); break;
    case(02):
        sprite.setTexture(Shared::boxTexture);
        sprite.setScale(0.25, 0.25);
        sprite.setTextureRect(sf::IntRect(721, 0 , 481, 720)); break;
    case(03):
        sprite.setTexture(Shared::boxTexture);
        sprite.setTextureRect(sf::IntRect(1480,362 ,2120-1480 ,719-362)); break;
    case(04):
        sprite.setTextureRect(sf::IntRect(2200,362 ,2840-2200 ,719-362)); break;
    case(05):
        sprite.setTexture(Shared::boxTexture);
        sprite.setTextureRect(sf::IntRect(24,1021 ,716-24 ,1440-1021)); break;
    case(06):
        sprite.setTextureRect(sf::IntRect(765,1021 ,1412-765 ,1440-1021)); break;
    case(07):
        sprite.setTexture(Shared::serreTexture);
        sprite.setTextureRect(sf::IntRect(37,287 ,2372-37 , 1919 - 287)); break;
    case(8):
        sprite.setTextureRect(sf::IntRect((140-37)+2545, 287, 4658- (140 - 37) + 2545, 1919-287)); break;
    case(9):
        sprite.setTexture(Shared::antenneTexture);
        sprite.setTextureRect(sf::IntRect(87,27 ,1137-87 ,1679-27)); break;
    case(10):
        sprite.setTextureRect(sf::IntRect(1286,27 ,2335- 1286, 1679 - 27)); break;
    case(11):
        sprite.setTexture(Shared::carTexture);
        sprite.setTextureRect(sf::IntRect(326- (1730 - 1472),838 ,1223-116 ,477-838)); break;
    case(12):
        sprite.setTextureRect(sf::IntRect(1472, 838,2780-1472, 477 - 838)); break;
    case(13):
        sprite.setTexture(Shared::lampadaireTexture);
        sprite.setTextureRect(sf::IntRect(1193,167 ,1584-1193 ,1272-167)); break;
    case(14):
        sprite.setTextureRect(sf::IntRect(2113, 167,2543-2113 , 1272 - 167)); break;
    case(15):
        sprite.setTexture(Shared::panneauTexture);
        sprite.setTextureRect(sf::IntRect(28,59 ,1637-28 ,1091-59)); break;
    case(16):
        sprite.setTextureRect(sf::IntRect(1708, 59,0 , 3317-1708 -59)); break;
    case(17):
        sprite.setTexture(Shared::eolienneTexture);
        sprite.setTextureRect(sf::IntRect(11,0 ,0 ,0)); break;
    case(18):
        sprite.setTextureRect(sf::IntRect(21,0 ,0 ,0)); break;
    default:
        return;
        sprite.setScale(0.5, 0.5);
        sprite.setPosition(x, y);
    }
}

void Reparable::fixing() {
    type -= 1;
    fixed = true;
    setSprite(type);
}

sf::Sprite Reparable::getSprite() const { return sprite; }