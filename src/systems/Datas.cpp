#include "Datas.hpp"

//font 
sf::Font Shared::font;

// assets du joueur
sf::Texture Shared::playerTexture;
sf::Texture Shared::smokeTexture;
sf::Texture Shared::swordTexture;
sf::Texture Shared::projectileTexture;

//assets des ennemis
sf::Texture Shared::ennemyTexture;

//assets des tiles
sf::Texture Shared::groundTexture;
sf::Texture Shared::floorTexture;

//sf::Sprite groundSprite;

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