#include "Menu.hpp"
#include <iostream>

void Menu::initFont() {
    if (!font.loadFromFile("assets/fonts/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
    }
}

Menu::Menu() {
    initFont();
}

int Menu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    // Gestion de l'événement de clic de souris
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        for (auto& button : buttons) {
            if (button.handleMouseClick(mousePos)) {
                return 1;  // Retourner une valeur spécifique pour l'action du bouton
            }
        }
    }

    // Gestion du survol de la souris
    for (auto& button : buttons) {
        button.handleMouseHover(mousePos);
    }

    return 0;  // Retourner 0 si aucune action n'a été prise
}

void Menu::render(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.render(window);
    }
}