#ifndef CONTROL_MENU_HPP
#define CONTROL_MENU_HPP

#include "Menu.hpp"
#include "Button.hpp"
#include "../../systems/Datas.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

class ControlMenu : public Menu {
private:
    Button* moveRightButton;
    Button* moveLeftButton;
    Button* jumpButton;
    Button* boostButton;
    Button* meleeAttackButton;
    Button* energyProjectileButton;
    Button* vitalSeedButton;
    Button* repairButton;
    Button* saveButton;

    sf::Keyboard::Key moveRightKey;
    sf::Keyboard::Key moveLeftKey;
    sf::Keyboard::Key jumpKey;
    sf::Keyboard::Key boostKey;
    sf::Keyboard::Key meleeAttackKey;
    sf::Keyboard::Key energyProjectileKey;
    sf::Keyboard::Key vitalSeedKey;
    sf::Keyboard::Key repairKey;

    bool waitingForKey;
    Button* buttonWaitingForKey;

    void initButtons();
    void setKeyBinding(sf::Keyboard::Key key);

public:
    ControlMenu();
    ~ControlMenu();

    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
    void render(sf::RenderWindow& window) override;
    void renderKeyBindings(sf::RenderWindow& window);
};

#endif // CONTROL_MENU_HPP