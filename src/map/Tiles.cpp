#include "Tiles.hpp"

Tiles::Tiles(float x, float y, int type)  : x(x), y(y), type(type) {
	sprite.setTexture(Shared::floorTexture);
	isReparable = false;
    setSprite(type);
	sprite.setScale(0.5, 0.5);
	sprite.setPosition(x, y);

    shadowShape.setFillColor(sf::Color(255, 255, 255, 128));
}

void Tiles::setSprite(int type) {
    switch (type)
    {
    case(00):
        sprite.setTextureRect(sf::IntRect(0 * size, 0 * 240, 240, 240)); break;
    case(01):
        sprite.setTextureRect(sf::IntRect(0 * 240, 0 * 240, 240, 240)); break;
    case(02):
        sprite.setTextureRect(sf::IntRect(1 * 240, 0 * 240, 240, 240)); break;
    case(03):
        sprite.setTextureRect(sf::IntRect(2 * 240, 0 * 240, 240, 240)); break;
    case(04):
        sprite.setTextureRect(sf::IntRect(0 * 240, 1 * 240, 240, 240)); break;
    case(05):
        sprite.setTextureRect(sf::IntRect(1 * 240, 1 * 240, 240, 240)); break;
    case(06):
        sprite.setTextureRect(sf::IntRect(2 * 240, 1 * 240, 240, 240)); break;
    case(07):
        sprite.setTextureRect(sf::IntRect(0 * 240, 2 * 240, 240, 240)); break;
    case(8):
        sprite.setTextureRect(sf::IntRect(1 * 240, 2 * 240, 240, 240)); break;
    case(9):
        sprite.setTextureRect(sf::IntRect(2 * 240, 2 * 240, 240, 240)); break;
    case(10):
        sprite.setTextureRect(sf::IntRect(3 * 240, 0 * 240, 240, 240)); break;
    case(11):
        sprite.setTextureRect(sf::IntRect(4 * 240, 0 * 240, 240, 240)); break;
    case(12):
        sprite.setTextureRect(sf::IntRect(5 * 240, 0 * 240, 240, 240)); break;
    case(13):
        sprite.setTextureRect(sf::IntRect(3 * 240, 1 * 240, 240, 240)); break;
    case(14):
        sprite.setTextureRect(sf::IntRect(4 * 240, 1 * 240, 240, 240)); break;
    case(15):
        sprite.setTextureRect(sf::IntRect(5 * 240, 1 * 240, 240, 240)); break;
    case(16):
        sprite.setTextureRect(sf::IntRect(3 * 240, 2 * 240, 240, 240)); break;
    case(17):
        sprite.setTextureRect(sf::IntRect(4 * 240, 2 * 240, 240, 240)); break;
    case(18):
        sprite.setTextureRect(sf::IntRect(5 * 240, 2 * 240, 240, 240)); break;
    case(19):
        sprite.setTextureRect(sf::IntRect(6 * 240, 0 * 240, 240, 240)); break;
    case(20):
        sprite.setTextureRect(sf::IntRect(7 * 240, 0 * 240, 240, 240)); break;
    case(21):
        sprite.setTextureRect(sf::IntRect(8 * 240, 0 * 240, 240, 240)); break;
    case(22):
        sprite.setTextureRect(sf::IntRect(6 * 240, 1 * 240, 240, 240)); break;
    case(23):
        sprite.setTextureRect(sf::IntRect(7 * 240, 1 * 240, 240, 240)); break;
    case(24):
        sprite.setTextureRect(sf::IntRect(8 * 240, 1 * 240, 240, 240)); break;
    case(25):
        sprite.setTextureRect(sf::IntRect(6 * 240, 2 * 240, 240, 240)); break;
    case(26):
        sprite.setTextureRect(sf::IntRect(0 * 240, 3 * 240, 240, 240)); break;
    case(27):
        sprite.setTextureRect(sf::IntRect(1 * 240, 3 * 240, 240, 240)); break;
    case(28):
        sprite.setTextureRect(sf::IntRect(2 * 240, 3 * 240, 240, 240)); break;
    case(29):
        sprite.setTextureRect(sf::IntRect(3 * 240, 3 * 240, 240, 240)); break;
    case(30):
        sprite.setTextureRect(sf::IntRect(0 * 240, 4 * 240, 240, 240)); break;
    case(31):
        sprite.setTextureRect(sf::IntRect(1 * 240, 4 * 240, 240, 240)); break;
    case(32):
        sprite.setTextureRect(sf::IntRect(2 * 240, 4 * 240, 240, 240)); break;
    case(33):
        sprite.setTextureRect(sf::IntRect(3 * 240, 4 * 240, 240, 240)); break;
    case(34):
        sprite.setTextureRect(sf::IntRect(9 * 240, 5 * 240, 240, 240)); break;
    case(35):
        sprite.setTextureRect(sf::IntRect(10 * 240, 5 * 240, 240, 240)); break;
    case(36):
        sprite.setTextureRect(sf::IntRect(11 * 240, 5 * 240, 240, 240)); break;
    case(37):
        sprite.setTextureRect(sf::IntRect(9 * 240, 6 * 240, 240, 240)); break;
    case(38):
        sprite.setTextureRect(sf::IntRect(10 * 240, 6 * 240, 240, 240)); break;
    case(39):
        sprite.setTextureRect(sf::IntRect(11 * 240, 6 * 240, 240, 240)); break;
    case(40):
        sprite.setTextureRect(sf::IntRect(8 * 240, 2 * 240, 240, 240)); break;
    case(41):
        sprite.setTextureRect(sf::IntRect(9 * 240, 2 * 240, 240, 240)); break;
    case(42):
        sprite.setTextureRect(sf::IntRect(10 * 240, 2 * 240, 240, 240)); break;
    case(43):
        sprite.setTextureRect(sf::IntRect(8 * 240, 3 * 240, 240, 240)); break;
    case(44):
        sprite.setTextureRect(sf::IntRect(9 * 240, 3 * 240, 240, 240)); break;
    case(45):
        sprite.setTextureRect(sf::IntRect(10 * 240, 3 * 240, 240, 240)); break;
    case(46):
        sprite.setTextureRect(sf::IntRect(8 * 240, 4 * 240, 240, 240)); break;
    case(47):
        sprite.setTextureRect(sf::IntRect(9 * 240, 4 * 240, 240, 240)); break;
    case(48):
        sprite.setTextureRect(sf::IntRect(10 * 240, 4 * 240, 240, 240)); break;
    case(49):
        sprite.setTextureRect(sf::IntRect(11 * 240, 4 * 240, 240, 240)); break;
    case(50):
        sprite.setTextureRect(sf::IntRect(0 * 240, 5 * 240, 240, 240)); break;
    case(51):
        sprite.setTextureRect(sf::IntRect(1 * 240, 5 * 240, 240, 240)); break;
    case(52):
        sprite.setTextureRect(sf::IntRect(2 * 240, 5 * 240, 240, 240)); break;
    case(53):
        sprite.setTextureRect(sf::IntRect(0 * 240, 6 * 240, 240, 240)); break;
    case(54):
        sprite.setTextureRect(sf::IntRect(1 * 240, 6 * 240, 240, 240)); break;
    case(55):
        sprite.setTextureRect(sf::IntRect(2 * 240, 6 * 240, 240, 240)); break;
    case(56):
        sprite.setTextureRect(sf::IntRect(0 * 240, 7 * 240, 240, 240)); break;
    case(57):
        sprite.setTextureRect(sf::IntRect(1 * 240, 7 * 240, 240, 240)); break;
    case(58):
        sprite.setTextureRect(sf::IntRect(2 * 240, 7 * 240, 240, 240)); break;
    case(59):
        sprite.setTextureRect(sf::IntRect(3 * 240, 5 * 240, 240, 240)); break;
    case(60):
        sprite.setTextureRect(sf::IntRect(4 * 240, 5 * 240, 240, 240)); break;
    case(61):
        sprite.setTextureRect(sf::IntRect(5 * 240, 5 * 240, 240, 240)); break;
    case(62):
        sprite.setTextureRect(sf::IntRect(3 * 240, 6 * 240, 240, 240)); break;
    case(63):
        sprite.setTextureRect(sf::IntRect(4 * 240, 6 * 240, 240, 240)); break;
    case(64):
        sprite.setTextureRect(sf::IntRect(5 * 240, 6 * 240, 240, 240)); break;
    case(65):
        sprite.setTextureRect(sf::IntRect(3 * 240, 7 * 240, 240, 240)); break;
    case(66):
        sprite.setTextureRect(sf::IntRect(4 * 240, 7 * 240, 240, 240)); break;
    case(67):
        sprite.setTextureRect(sf::IntRect(5 * 240, 7 * 240, 240, 240)); break;
    case(68):
        sprite.setTextureRect(sf::IntRect(0 * 240, 8 * 240, 240, 240)); break;
    case(69):
        sprite.setTextureRect(sf::IntRect(1 * 240, 8 * 240, 240, 240)); break;
    case(70):
        sprite.setTextureRect(sf::IntRect(2 * 240, 8 * 240, 240, 240)); break;
    case(71):
        sprite.setTextureRect(sf::IntRect(3 * 240, 8 * 240, 240, 240)); break;
    case(72):
        sprite.setTextureRect(sf::IntRect(4 * 240, 8 * 240, 240, 240)); break;
    case(73):
        sprite.setTextureRect(sf::IntRect(5 * 240, 8 * 240, 240, 240)); break;
    case(74):
        sprite.setTextureRect(sf::IntRect(6 * 240, 7 * 240, 240, 240)); break;
    case(75):
        sprite.setTextureRect(sf::IntRect(7 * 240, 7 * 240, 240, 240)); break;
    case(76):
        sprite.setTextureRect(sf::IntRect(8 * 240, 7 * 240, 240, 240)); break;
    case(77):
        sprite.setTextureRect(sf::IntRect(9 * 240, 7 * 240, 240, 240)); break;
    case(78):
        sprite.setTextureRect(sf::IntRect(6 * 240, 8 * 240, 240, 240)); break;
    case(79):
        sprite.setTextureRect(sf::IntRect(7 * 240, 8 * 240, 240, 240)); break;
    case(80):
        sprite.setTextureRect(sf::IntRect(8 * 240, 8 * 240, 240, 240)); break;
    case(81):
        sprite.setTextureRect(sf::IntRect(9 * 240, 8 * 240, 240, 240)); break;
    case(82):
        sprite.setTextureRect(sf::IntRect(4 * 240, 3 * 240, 240, 240)); break;
    case(83):
        sprite.setTextureRect(sf::IntRect(5 * 240, 3 * 240, 240, 240)); break;
    case(84):
        sprite.setTextureRect(sf::IntRect(6 * 240, 3 * 240, 240, 240)); break;
    case(85):
        sprite.setTextureRect(sf::IntRect(7 * 240, 3 * 240, 240, 240)); break;
    case(86):
        sprite.setTextureRect(sf::IntRect(4 * 240, 4 * 240, 240, 240)); break;
    case(87):
        sprite.setTextureRect(sf::IntRect(5 * 240, 4 * 240, 240, 240)); break;
    case(88):
        sprite.setTextureRect(sf::IntRect(6 * 240, 4 * 240, 240, 240)); break;
    case(89):
        sprite.setTextureRect(sf::IntRect(7 * 240, 4 * 240, 240, 240)); break;
    case(90):
        sprite.setTextureRect(sf::IntRect(10 * 240, 7 * 240, 240, 240)); break;
    case(91):
        sprite.setTextureRect(sf::IntRect(11 * 240, 7 * 240, 240, 240)); break;
    case(92):
        sprite.setTextureRect(sf::IntRect(12 * 240, 7 * 240, 240, 240)); break;
    case(93):
        sprite.setTextureRect(sf::IntRect(10 * 240, 8 * 240, 240, 240)); break;
    case(94):
        sprite.setTextureRect(sf::IntRect(11 * 240, 8 * 240, 240, 240)); break;
    case(95):
        sprite.setTextureRect(sf::IntRect(12 * 240, 8 * 240, 240, 240)); break;
    case(96):
        sprite.setTextureRect(sf::IntRect(6 * 240, 5 * 240, 240, 240)); break;
    case(97):
        sprite.setTextureRect(sf::IntRect(7 * 240, 5 * 240, 240, 240)); break;
    case(98):
        sprite.setTextureRect(sf::IntRect(8 * 240, 5 * 240, 240, 240)); break;
    case(99):
        sprite.setTextureRect(sf::IntRect(6 * 240, 6 * 240, 240, 240)); break;
    case(100):
        sprite.setTextureRect(sf::IntRect(7 * 240, 6 * 240, 240, 240)); break;
    case(101):
        sprite.setTextureRect(sf::IntRect(8 * 240, 6 * 240, 240, 240)); break;
    case(102):
        sprite.setTextureRect(sf::IntRect(7 * 240, 2 * 240, 240, 240)); break;
    }
}

//-----------------------------------------------------Pour les ombres-----------------------------------------------------
void Tiles::setShadow(bool hasShadow) {
    isShadow = hasShadow;
}

bool Tiles::hasShadow() const {
    return isShadow;
}

sf::RectangleShape Tiles::getShadowShape() const {
	return shadowShape;
}

bool Tiles::isEmpty() const {
    return empty;
}

int Tiles::getValue() const {
    return value;
}
//-----------------------------------------------------Pour les ombres-----------------------------------------------------

Tiles::~Tiles() {}

sf::Vector2f Tiles::getPos() const { return sf::Vector2f(x, y); }

sf::Sprite Tiles::getSprite() const { return sprite; }