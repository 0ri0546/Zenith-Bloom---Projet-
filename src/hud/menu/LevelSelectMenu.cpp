#include "LevelSelector.hpp"

WorldSelectMenu::WorldSelectMenu() {
    initButtons();
}

void WorldSelectMenu::initButtons() {
    buttons.clear();

    // Créer un bouton pour chaque monde (niveau)
    for (int i = 0; i < 5; ++i) {
        std::string levelName = "World " + std::to_string(i + 1);
        buttons.push_back(Button(i, levelName, levelName, font, sf::Vector2f(100.f, 150.f + i * 100), sf::Vector2f(300.f, 50.f),
            [this, i]() {
                // Code pour charger le niveau correspondant
                std::cout << "World " << i + 1 << " selected!" << std::endl;
            }));
    }
}