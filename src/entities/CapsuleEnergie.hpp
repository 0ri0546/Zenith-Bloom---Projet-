#ifndef CAPSULE_ENERGIE_HPP
#define CAPSULE_ENERGIE_HPP

#include "../systems/Datas.hpp"
#include "../systems/AssetLoader.hpp"
#include "Player.hpp"

class CapsuleEnergie {
private:
    int energyValue;
    sf::Sprite sprite;
    float x, y;
	Assets assets;  
public:
    CapsuleEnergie(int valeur, sf::Texture& texture, float x, float y);
    ~CapsuleEnergie();

    void utiliser(Player& joueur);
    int getEnergyValue() const;
    sf::Sprite getSprite() const;
};

#endif