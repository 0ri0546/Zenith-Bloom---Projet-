#ifndef CONTROL_MENU_HPP
#define CONTROL_MENU_HPP

#include "../../systems/Datas.hpp"
#include "Menu.hpp"
#include "Button.hpp"


class ControlMenu : public Menu {
private:
    std::vector<Button> buttons;
    sf::Keyboard::Key moveRightKey;
    sf::Keyboard::Key moveLeftKey;
    sf::Keyboard::Key jumpKey;
    sf::Keyboard::Key vitalSeedKey;
    sf::Keyboard::Key repairKey;

    bool waitingForKey;
    Button* buttonWaitingForKey;

    void initButtons();
    void setKeyBinding(sf::Keyboard::Key key);

public:
    ControlMenu();

    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
    void render(sf::RenderWindow& window) override;
};

#endif // CONTROL_MENU_HPP