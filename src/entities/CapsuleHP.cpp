#include "CapsuleHP.hpp"

CapsuleHP::CapsuleHP(int valeur, sf::Texture& texture, float x, float y) : hpValue(valeur), x(x), y(y) {
	sprite.setTexture(texture);
	assets.resize(sprite, 50, 50);
	sprite.setPosition(x, y);
}

CapsuleHP::~CapsuleHP() {}

void CapsuleHP::utiliser(Player& joueur) {
	joueur.augmenterHP(hpValue);
}

int CapsuleHP::getHPValue() const { return hpValue; }
sf::Sprite CapsuleHP::getSprite() const { return sprite; }
