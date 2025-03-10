#include "MainMenu.hpp"
#include <iostream>

void MainMenu::initButtons() {
    buttons.emplace_back("Jouer", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 200), sf::Vector2f(200, 50), []() {
        std::cout << "Play button clicked!" << std::endl;
        });

    buttons.emplace_back("Options", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 300), sf::Vector2f(200, 50), []() {
        std::cout << "Options button clicked!" << std::endl;
        });

    buttons.emplace_back("Quitter", font, sf::Vector2f((Config::WINDOW_WIDTH - 200) / 2.f, 400), sf::Vector2f(200, 50), []() {
        std::cout << "Quit button clicked!" << std::endl;
        });
}

MainMenu::MainMenu() : Menu() {
    initButtons();
}

// Cette méthode peut être modifiée pour renvoyer différentes valeurs selon l'action effectuée
int MainMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    int result = Menu::handleInput(window, event);

    if (result == 1) { // Jouer
        std::cout << "Transitioning to game..." << std::endl;
        return 1;  // Par exemple, passer au menu du jeu
    }
    else if (result == 2) { // Options
        std::cout << "Opening options..." << std::endl;
        return 2;  // Par exemple, ouvrir le menu des options
    }
    else if (result == 3) { // Quitter
        window.close();
        return 3;  // Quitter le jeu
    }

    return 0;
}