#ifndef CAPSULE_HP_HPP
#define CAPSULE_HP_HPP

#include "../systems/Datas.hpp"
#include "../systems/AssetLoader.hpp"
#include "Player.hpp"

class CapsuleHP {
private:
    int hpValue;
    sf::Sprite sprite;
    float x, y;
    Assets assets;
public:
    CapsuleHP(int valeur, sf::Texture& texture, float x, float y);
    ~CapsuleHP();

    void utiliser(Player& joueur);
    int getHPValue() const;
    sf::Sprite getSprite() const;
};

#endif