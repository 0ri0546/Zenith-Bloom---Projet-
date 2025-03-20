#ifndef VIDEO_MENU_HPP
#define VIDEO_MENU_HPP

#include "Menu.hpp"

class VideoMenu : public Menu {
private:
    void initButtons() override;

    bool isFullscreen;
    bool isVSync;
    sf::Vector2u currentResolution;

public:
    enum MenuList { MAIN_MENU, PAUSE_MENU };

    MenuList lastMenu;

    VideoMenu(MenuList lastMenu);
    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
    void toggleFullscreen(sf::RenderWindow& window);
    void toggleVSync(sf::RenderWindow& window);
    void update(sf::RenderWindow& window);
};

#endif // VIDEO_MENU_HPP