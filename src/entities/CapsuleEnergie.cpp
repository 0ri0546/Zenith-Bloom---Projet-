#include "CapsuleEnergie.hpp"

CapsuleEnergie::CapsuleEnergie(int valeur, sf::Texture& texture, float x, float y) : energyValue(valeur), x(x), y(y) {
	sprite.setTexture(texture);
	assets.resize(sprite, 50, 50);
	sprite.setPosition(x, y);
}

CapsuleEnergie::~CapsuleEnergie() {}

void CapsuleEnergie::utiliser(Player& joueur) {
	joueur.augmenterEnergie(energyValue);
}

int CapsuleEnergie::getEnergyValue() const { return energyValue; }
sf::Sprite CapsuleEnergie::getSprite() const { return sprite; }
