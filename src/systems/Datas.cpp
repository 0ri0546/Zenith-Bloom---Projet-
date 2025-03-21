#include "Datas.hpp"

//font 
sf::Font Shared::font;

// assets du joueur
sf::Texture Shared::playerTexture;
sf::Texture Shared::playerReverseTexture;
sf::Texture Shared::smokeTexture;
sf::Texture Shared::swordTexture;
sf::Texture Shared::projectileTexture;
sf::Texture Shared::waterProjTexture;

//assets des ennemis
sf::Texture Shared::ennemyTexture;
sf::Texture Shared::ennemyTextureR;
sf::Texture Shared::tankTexture;
sf::Texture Shared::tankTextureR;
sf::Texture Shared::droneTexture;
sf::Texture Shared::droneTextureR;
sf::Texture Shared::incendTexture;
sf::Texture Shared::incendTextureR;
sf::Texture Shared::projIcend;
sf::Texture Shared::projMini;
sf::Texture Shared::flame;

//assets des tiles
sf::Texture Shared::groundTexture;
sf::Texture Shared::floorTexture;
sf::Texture Shared::itemsTexture;
sf::Texture Shared::capsuleHPTexture;
sf::Texture Shared::capsuleEnergyTexture;
sf::Texture Shared::propsTexture;
sf::Texture Shared::boxTexture;
sf::Texture Shared::serreTexture;
sf::Texture Shared::antenneTexture;
sf::Texture Shared::carTexture;
sf::Texture Shared::eolienneTexture;
sf::Texture Shared::lampadaireTexture;
sf::Texture Shared::panneauTexture;
//sf::Sprite groundSprite;

//assets du HUD
sf::Texture Shared::dayTexture;
sf::Texture Shared::nightTexture;
sf::Texture Shared::lifeBar2Texture;
sf::Texture Shared::energyBarTexture;
sf::Texture Shared::progressBarTexture;
sf::Texture Shared::surchauffeBarTexture;

//assets des background
sf::Texture Shared::backgroundTexture;

namespace Keybind {
    static std::unordered_map<Action, sf::Keyboard::Key> keyBindings = {
        {Action::MoveRight, sf::Keyboard::D},
        {Action::MoveLeft, sf::Keyboard::Q},
        {Action::Jump, sf::Keyboard::Space},
        {Action::VitalSeed, sf::Keyboard::T},
        {Action::Repair, sf::Keyboard::R}
    };

    void setKey(Action action, sf::Keyboard::Key key) {
        keyBindings[action] = key;
    }

    sf::Keyboard::Key getKey(Action action) {
        return keyBindings[action];
    }
}