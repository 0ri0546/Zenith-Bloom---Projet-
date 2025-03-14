#include "ControlMenu.hpp"
#include <iostream>

std::string keyToString(sf::Keyboard::Key key) {
    switch (key) {
    case sf::Keyboard::A: return "A";
    case sf::Keyboard::B: return "B";
    case sf::Keyboard::C: return "C";
    case sf::Keyboard::D: return "D";
    case sf::Keyboard::E: return "E";
    case sf::Keyboard::F: return "F";
    case sf::Keyboard::G: return "G";
    case sf::Keyboard::H: return "H";
    case sf::Keyboard::I: return "I";
    case sf::Keyboard::J: return "J";
    case sf::Keyboard::K: return "K";
    case sf::Keyboard::L: return "L";
    case sf::Keyboard::M: return "M";
    case sf::Keyboard::N: return "N";
    case sf::Keyboard::O: return "O";
    case sf::Keyboard::P: return "P";
    case sf::Keyboard::Q: return "Q";
    case sf::Keyboard::R: return "R";
    case sf::Keyboard::S: return "S";
    case sf::Keyboard::T: return "T";
    case sf::Keyboard::U: return "U";
    case sf::Keyboard::V: return "V";
    case sf::Keyboard::W: return "W";
    case sf::Keyboard::X: return "X";
    case sf::Keyboard::Y: return "Y";
    case sf::Keyboard::Z: return "Z";
    case sf::Keyboard::Num0: return "0";
    case sf::Keyboard::Num1: return "1";
    case sf::Keyboard::Num2: return "2";
    case sf::Keyboard::Num3: return "3";
    case sf::Keyboard::Num4: return "4";
    case sf::Keyboard::Num5: return "5";
    case sf::Keyboard::Num6: return "6";
    case sf::Keyboard::Num7: return "7";
    case sf::Keyboard::Num8: return "8";
    case sf::Keyboard::Num9: return "9";
    case sf::Keyboard::Space: return "Espace";
    case sf::Keyboard::Escape: return "Echape";
    case sf::Keyboard::Enter: return "Entrer";
    case sf::Keyboard::BackSpace: return "Retour";
    case sf::Keyboard::Tab: return "Tab";
    case sf::Keyboard::LShift: return "L Maj";
    case sf::Keyboard::RShift: return "R Maj";
    case sf::Keyboard::LControl: return "L Controle";
    case sf::Keyboard::RControl: return "R Controle";
    case sf::Keyboard::LAlt: return "L Alt";
    case sf::Keyboard::RAlt: return "R Alt";
    default: return "Unknown";
    }
}

ControlMenu::ControlMenu() : Menu(), waitingForKey(false), buttonWaitingForKey(nullptr) {
    initButtons();

    moveRightKey = Keybind::getKey(Keybind::Action::MoveRight);
    moveLeftKey = Keybind::getKey(Keybind::Action::MoveLeft);
    jumpKey = Keybind::getKey(Keybind::Action::Jump);
    boostKey = Keybind::getKey(Keybind::Action::Boost);
    vitalSeedKey = Keybind::getKey(Keybind::Action::VitalSeed);
    repairKey = Keybind::getKey(Keybind::Action::Repair);
}

ControlMenu::~ControlMenu() {
    delete moveRightButton;
    delete moveLeftButton;
    delete jumpButton;
    delete boostButton;
    delete vitalSeedButton;
    delete repairButton;
}

void ControlMenu::initButtons() {
    float windowWidth = Config::WINDOW_WIDTH;
    float windowHeight = Config::WINDOW_HEIGHT;

    float centerX = windowWidth / 2.f;

    float verticalSpacing = 100.f;
    float startY = 150.f;

    Button* backButton = new Button(1, "Retour", "Retour", font, sf::Vector2f(centerX - 150, startY), sf::Vector2f(300, 50), [this]() {});
    buttons.push_back(backButton);

    moveRightButton = new Button(2, "Aller à droite : D", "Aller à droite", font, sf::Vector2f(centerX - 150, startY + verticalSpacing), sf::Vector2f(300, 50), [this]() {
        buttonWaitingForKey = moveRightButton;
        waitingForKey = true;
        });
    moveLeftButton = new Button(3, "Aller à gauche = Q", "Aller à gauche", font, sf::Vector2f(centerX - 150, startY + 2 * verticalSpacing), sf::Vector2f(300, 50), [this]() {
        buttonWaitingForKey = moveLeftButton;
        waitingForKey = true;
        });
    jumpButton = new Button(4, "Sauter = Espace", "Sauter", font, sf::Vector2f(centerX - 150, startY + 3 * verticalSpacing), sf::Vector2f(300, 50), [this]() {
        buttonWaitingForKey = jumpButton;
        waitingForKey = true;
        });
    boostButton = new Button(5, "Boost = Maj", "Boost", font, sf::Vector2f(centerX - 150, startY + 4 * verticalSpacing), sf::Vector2f(300, 50), [this]() {
        buttonWaitingForKey = boostButton;
        waitingForKey = true;
        });
    vitalSeedButton = new Button(6, "Graine vitale = T", "Graine vitale", font, sf::Vector2f(centerX - 150, startY + 5 * verticalSpacing), sf::Vector2f(300, 50), [this]() {
        buttonWaitingForKey = vitalSeedButton;
        waitingForKey = true;
        });
    repairButton = new Button(7, "Réparation = R", "Réparation", font, sf::Vector2f(centerX - 150, startY + 6 * verticalSpacing), sf::Vector2f(300, 50), [this]() {
        buttonWaitingForKey = repairButton;
        waitingForKey = true;
        });

    buttons.push_back(moveRightButton);
    buttons.push_back(moveLeftButton);
    buttons.push_back(jumpButton);
    buttons.push_back(boostButton);
    buttons.push_back(vitalSeedButton);
    buttons.push_back(repairButton);
}

int ControlMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    if (waitingForKey) {
        if (event.type == sf::Event::KeyPressed) {
            setKeyBinding(event.key.code);
            buttonWaitingForKey->setText(buttonWaitingForKey->getOriginalText() + " : " + keyToString(event.key.code));
            waitingForKey = false;
        }
    }
    else {
        if (event.type == sf::Event::MouseButtonPressed) {
            for (auto& button : buttons) {
                int buttonResult = button->handleMouseClick(mousePos);
                if (buttonResult != 0) {
                    if (buttonResult >= 2 && buttonResult <= 7) {
                        buttonWaitingForKey = button;
                        button->setText("Appuyez sur une touche...");
                        waitingForKey = true;
                    }
                    return buttonResult;
                }
            }
        }
    }

    for (auto& button : buttons) {
        button->handleMouseHover(mousePos);
    }

    return 0;
}

void ControlMenu::render(sf::RenderWindow& window) {
    renderKeyBindings(window);

    window.clear();
    window.draw(backgroundSprite);
    for (auto& button : buttons) {
        button->render(window);
    }
}

void ControlMenu::renderKeyBindings(sf::RenderWindow& window) {
    moveRightButton->setText("Aller à droite : " + keyToString(moveRightKey));
    moveLeftButton->setText("Aller à gauche : " + keyToString(moveLeftKey));
    jumpButton->setText("Sauter : " + keyToString(jumpKey));
    boostButton->setText("Boost : " + keyToString(boostKey));
    vitalSeedButton->setText("Graine vitale : " + keyToString(vitalSeedKey));
    repairButton->setText("Réparation : " + keyToString(repairKey));
}

void ControlMenu::setKeyBinding(sf::Keyboard::Key key) {
    if (buttonWaitingForKey == moveRightButton) {
        moveRightKey = key;
        buttonWaitingForKey->setText("Aller à droite : " + keyToString(moveRightKey));
        Keybind::setKey(Keybind::Action::MoveRight, moveRightKey);
    }
    else if (buttonWaitingForKey == moveLeftButton) {
        moveLeftKey = key;
        buttonWaitingForKey->setText("Aller à gauche : " + keyToString(moveLeftKey));
        Keybind::setKey(Keybind::Action::MoveLeft, moveLeftKey);
    }
    else if (buttonWaitingForKey == jumpButton) {
        jumpKey = key;
        buttonWaitingForKey->setText("Sauter : " + keyToString(jumpKey));
        Keybind::setKey(Keybind::Action::Jump, jumpKey);
    }
    else if (buttonWaitingForKey == boostButton) {
        boostKey = key;
        buttonWaitingForKey->setText("Boost : " + keyToString(boostKey));
        Keybind::setKey(Keybind::Action::Boost, boostKey);
    }
    else if (buttonWaitingForKey == vitalSeedButton) {
        vitalSeedKey = key;
        buttonWaitingForKey->setText("Graine vitale : " + keyToString(vitalSeedKey));
        Keybind::setKey(Keybind::Action::VitalSeed, vitalSeedKey);
    }
    else if (buttonWaitingForKey == repairButton) {
        repairKey = key;
        buttonWaitingForKey->setText("Réparation : " + keyToString(repairKey));
        Keybind::setKey(Keybind::Action::Repair, repairKey);
    }

    waitingForKey = false;
}