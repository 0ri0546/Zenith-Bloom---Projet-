#include "CapsuleEnergie.hpp"

CapsuleEnergie::CapsuleEnergie(int valeur, sf::Texture& texture, float x, float y) : valeurEnergie(valeur), x(x), y(y) {
	sprite.setTexture(texture);
	assets.resize(sprite, 50, 50);
	sprite.setPosition(x, y);
}

CapsuleEnergie::~CapsuleEnergie() {}

void CapsuleEnergie::utiliser(Player& joueur) {
    joueur.ajouterEnergie(valeurEnergie);
}

int CapsuleEnergie::getValeurEnergie() const { return valeurEnergie; }
