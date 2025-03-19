#include "Datas.hpp"

//font 
sf::Font Shared::font;

// assets du joueur
sf::Texture Shared::playerTexture;
sf::Texture Shared::playerReverseTexture;
sf::Texture Shared::smokeTexture;
sf::Texture Shared::swordTexture;
sf::Texture Shared::projectileTexture;

//assets des ennemis
sf::Texture Shared::ennemyTexture;
sf::Texture Shared::ennemyTextureR;
sf::Texture Shared::tankTexture;
sf::Texture Shared::tankTextureR;
sf::Texture Shared::droneTexture;
sf::Texture Shared::droneTextureR;
sf::Texture Shared::incendTexture;
sf::Texture Shared::incendTextureR;

//assets des tiles
sf::Texture Shared::groundTexture;
sf::Texture Shared::floorTexture;
sf::Texture Shared::itemsTexture;
//sf::Sprite groundSprite;

//assets du HUD
sf::Texture Shared::dayTexture;
sf::Texture Shared::nightTexture;
sf::Texture Shared::progressBarTexture;

//assets des menus

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