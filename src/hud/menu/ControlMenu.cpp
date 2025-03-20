#include "ControlMenu.hpp"

std::string keyToString(sf::Keyboard::Key key) {
    static const std::map<sf::Keyboard::Key, std::string> keyMap = {
        {sf::Keyboard::A, "A"}, {sf::Keyboard::B, "B"}, {sf::Keyboard::C, "C"},
        {sf::Keyboard::D, "D"}, {sf::Keyboard::E, "E"}, {sf::Keyboard::F, "F"},
        {sf::Keyboard::G, "G"}, {sf::Keyboard::H, "H"}, {sf::Keyboard::I, "I"},
        {sf::Keyboard::J, "J"}, {sf::Keyboard::K, "K"}, {sf::Keyboard::L, "L"},
        {sf::Keyboard::M, "M"}, {sf::Keyboard::N, "N"}, {sf::Keyboard::O, "O"},
        {sf::Keyboard::P, "P"}, {sf::Keyboard::Q, "Q"}, {sf::Keyboard::R, "R"},
        {sf::Keyboard::S, "S"}, {sf::Keyboard::T, "T"}, {sf::Keyboard::U, "U"},
        {sf::Keyboard::V, "V"}, {sf::Keyboard::W, "W"}, {sf::Keyboard::X, "X"},
        {sf::Keyboard::Y, "Y"}, {sf::Keyboard::Z, "Z"},
        {sf::Keyboard::Num0, "0"}, {sf::Keyboard::Num1, "1"}, {sf::Keyboard::Num2, "2"},
        {sf::Keyboard::Num3, "3"}, {sf::Keyboard::Num4, "4"}, {sf::Keyboard::Num5, "5"},
        {sf::Keyboard::Num6, "6"}, {sf::Keyboard::Num7, "7"}, {sf::Keyboard::Num8, "8"},
        {sf::Keyboard::Num9, "9"},
        {sf::Keyboard::Space, "Espace"}, {sf::Keyboard::Escape, "Echape"},
        {sf::Keyboard::Enter, "Entrer"}, {sf::Keyboard::BackSpace, "Retour"},
        {sf::Keyboard::Tab, "Tab"}, {sf::Keyboard::LShift, "Maj Gauche"},
        {sf::Keyboard::RShift, "Maj Droite"}, {sf::Keyboard::LControl, "Controle Gauche"},
        {sf::Keyboard::RControl, "Controle Droite"}, {sf::Keyboard::LAlt, "Alt Gauche"},
        {sf::Keyboard::RAlt, "Alt Droite"}
    };
    auto it = keyMap.find(key);
    return (it != keyMap.end()) ? it->second : "Unknown";
}

ControlMenu::ControlMenu() : Menu(), waitingForKey(false), buttonWaitingForKey(nullptr) {
    initButtons();
}

void ControlMenu::initButtons() {
    float centerX = Config::WINDOW_WIDTH / 2.f;
    float startY = 200.f;
    float verticalSpacing = 100.f;

    buttons.emplace_back(1, "Retour", "Retour", Shared::font, sf::Vector2f(centerX - 150, startY), sf::Vector2f(300, 50), []() {});

    auto addButton = [&](int id, Keybind::Action action, const std::string& label, float offsetY) {
        buttons.emplace_back(id, label + " : " + keyToString(Keybind::getKey(action)), label, Shared::font, sf::Vector2f(centerX - 150, startY + offsetY), sf::Vector2f(300, 50), [this, id]() {
            for (auto& button : buttons) {
                if (button.getId() == id) {
                    buttonWaitingForKey = &button;
                    buttonWaitingForKey->setText("Appuyez sur une touche...");
                    waitingForKey = true;
                    break;
                }
            }
        });
    };

    addButton(2, Keybind::Action::MoveRight, "Aller à droite", verticalSpacing);
    addButton(3, Keybind::Action::MoveLeft, "Aller à gauche", 2 * verticalSpacing);
    addButton(4, Keybind::Action::Jump, "Sauter", 3 * verticalSpacing);
    addButton(5, Keybind::Action::VitalSeed, "Graine vitale", 4 * verticalSpacing);
    addButton(6, Keybind::Action::Repair, "Réparation", 5 * verticalSpacing);

    if (isGamepadConnected && !buttons.empty()) {
        currentHoveredButtonIndex = 0;
        updateHoverForButton(currentHoveredButtonIndex);
    }
}

int ControlMenu::handleInput(sf::RenderWindow& window, const sf::Event& event) {
    int parentResult = Menu::handleInput(window, event);
    if (parentResult != 0) return parentResult;

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    static bool newClick = false;

    if (waitingForKey && event.type == sf::Event::KeyPressed) {
        setKeyBinding(event.key.code);
        waitingForKey = false;
        newClick = true;
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && newClick) {
        newClick = false;
        for (auto& button : buttons) {
            int result = button.handleInput(mousePos, event);
            if (result == 1) {
                return result;
            }
            else if (result >= 2 && result <= 6) {
                buttonWaitingForKey = &button;
                buttonWaitingForKey->setText("Appuyez sur une touche...");
                waitingForKey = true;
                return result;
            }
        }
    }
    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        newClick = true;
    }
    for (auto& button : buttons) {
        button.handleMouseHover(mousePos);
    }
    return 0;
}


void ControlMenu::render(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    for (auto& button : buttons) {
        button.render(window);
    }
}

void ControlMenu::setKeyBinding(sf::Keyboard::Key key) {
    if (!buttonWaitingForKey) return;
    buttonWaitingForKey->setText(buttonWaitingForKey->getOriginalText() + " : " + keyToString(key));
    Keybind::setKey(static_cast<Keybind::Action>(buttonWaitingForKey->getId() - 2), key);
}