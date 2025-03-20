#ifndef WORLDSELECTMENU_HPP
#define WORLDSELECTMENU_HPP

#include "Menu.hpp"
#include "Button.hpp"
#include <vector>

class LevelSelectMenu : public Menu {
private:
    virtual void initButtons() override;

public:
    LevelSelectMenu();
    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
};

#endif // WORLDSELECTMENU_HPP