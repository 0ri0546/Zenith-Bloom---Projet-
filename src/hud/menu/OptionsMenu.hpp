#ifndef OPTIONS_MENU_HPP
#define OPTIONS_MENU_HPP

#include "Menu.hpp"

class OptionsMenu : public Menu {
private:
    void initButtons();

public:
    enum MenuList { MAIN_MENU, PAUSE_MENU };

    MenuList lastMenu;

    OptionsMenu(MenuList lastMenu);
    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
};

#endif // OPTIONS_MENU_HPP