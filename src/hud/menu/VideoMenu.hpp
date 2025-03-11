#ifndef VIDEO_MENU_HPP
#define VIDEO_MENU_HPP

#include "Menu.hpp"

class VideoMenu : public Menu {
private:
    void initButtons() override;

    bool isFullscreen;
    sf::Vector2u currentResolution;

public:
    VideoMenu();
    int handleInput(sf::RenderWindow& window, const sf::Event& event) override;
    void toggleFullscreen(sf::RenderWindow& window);
    void changeResolution(sf::RenderWindow& window);
};

#endif // VIDEO_MENU_HPP