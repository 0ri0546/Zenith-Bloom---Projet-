#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../systems/Datas.hpp"
#include "../systems/AssetLoader.hpp"
#include "../systems/grid.hpp"
#include "../map/Platform.hpp"
#include "../map/Map.hpp"

#include "../entities/Player.hpp"
#include "../entities/Tank.hpp"
#include "../entities/FSM.hpp"
#include "../entities/CapsuleEnergie.hpp"
#include "../entities/CapsuleHP.hpp"

#include "../hud/menu/BouncingTitle.hpp"
#include "../hud/menu/MainMenu.hpp"
#include "../hud/menu/PauseMenu.hpp"
#include "../hud/menu/OptionsMenu.hpp"
#include "../hud/menu/VideoMenu.hpp"
#include "../hud/menu/SoundMenu.hpp"
#include "../hud/menu/ControlMenu.hpp"
#include "../hud/menu/GameOverMenu.hpp"
#include "../hud/menu/LevelSelectorMenu.hpp"

class Game {
public:
    Game();
    void run();

    enum class GameState {
        PLAYING,
        MAIN_MENU,
        LEVEL_SELECTOR_MENU,
        PAUSE_MENU,
        OPTIONS_MENU,
        VIDEO_MENU,
        SOUND_MENU,
        CONTROL_MENU,
        GAMEOVER_MENU,
        VICTORY_MENU,
        TITLE_MENU,
        EDITOR
    };

private:
    // fenetre et affichage
    sf::RenderWindow window;
    sf::View view;
    sf::Clock cycleClock;

    // catrographie et elements de jeu
    Map gamemap;
    std::vector<Platform> platforms;
    std::vector<std::unique_ptr<Ennemy>> ennemies;
    std::vector<std::unique_ptr<CapsuleHP>> capsulesHP;
    std::vector<std::unique_ptr<CapsuleEnergie>> capsulesEnergy;
    std::vector<std::unique_ptr<Shadow>> shadows;
    std::vector<Tank> Tanks;

    // player et etats du jeu
    Player player;
    bool isRunning = false;
    bool isGamePaused = false;
    bool isDay = true;
    bool gameStarted = false;
    bool textFall = false;
    bool isInTheSun = false;

    GameState currentState;
    BouncingTitle title;

    // menus
    MainMenu mainMenu;
    PauseMenu pauseMenu;
    OptionsMenu optionsMenu;
    VideoMenu videoMenu;
    SoundMenu soundMenu;
    ControlMenu controlMenu;
    GameOverMenu gameOverScreen;
    LevelSelectMenu levelSelectMenu;

    // methodes privées
    void createWindow();
    void processEvents(float deltaTime);
    void update(float deltaTime);
    void render();
    void handleState(const sf::Event& event, float deltaTime);
    void handleKeyboardInput(const sf::Event& event);
    void handleGamepadInput(float deltaTime);
    void cycleDayNight();
};

#endif