#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include "../systems/Datas.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "../map/Map.hpp"
#include "../hud/menu/MainMenu.hpp"
#include "../hud/menu/PauseMenu.hpp"
#include "../hud/menu/OptionsMenu.hpp"
#include "../hud/menu/VideoMenu.hpp"
#include "../hud/menu/SoundMenu.hpp"
#include "../hud/menu/ControlMenu.hpp"
#include "../entities/FSM.hpp"
#include "../entities/Tank.hpp"
#include "../systems/grid.hpp"
#include "../hud/menu/BouncingTitle.hpp"
#include "../hud/menu/gameOverMenu.hpp"
#include "../hud/menu/LevelSelectorMenu.hpp"
#include "../entities/CapsuleEnergie.hpp"
#include "../entities/CapsuleHP.hpp"


class Game {
public:
	Game();
	void run();

	enum GameState {
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
	sf::RenderWindow window;
	Player player;
	sf::View view;
	Map gamemap;
	sf::Clock cycleClock;
	
	std::vector<Platform> platforms;
	vector<std::unique_ptr<Ennemy>> ennemies;
	vector<std::unique_ptr<CapsuleHP>> capsulesHP;
	vector<std::unique_ptr<CapsuleEnergie>> capsulesEnergy;
	vector<Tank> Tanks;
	
	//Grid grid = Grid(gamemap);

	bool isRunning;
	bool isGamePaused;
	bool isDay;
	bool gameStarted = false;
	bool textFall;
	bool isInTheSun;

	void createWindow();
	void processEvents(float deltaTime);
	void update(float deltaTime);
	void render();
	void handleState(const sf::Event& event, float deltaTime);
	void handleKeyboardInput(const sf::Event& event);
	void handleGamepadInput(float deltaTime);
	void cycleDayNight();

	BouncingTitle title;
	GameState currentState;
	MainMenu mainMenu;
	PauseMenu pauseMenu;
	OptionsMenu optionsMenu;
	VideoMenu videoMenu;
	SoundMenu soundMenu;
	ControlMenu controlMenu;
	GameOverMenu gameOverScreen;
	LevelSelectMenu levelSelectMenu;
};

#endif