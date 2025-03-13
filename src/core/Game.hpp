#ifndef GAME_HPP
#define GAME_HPP

#include "../systems/Datas.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "../map/Map.hpp"
#include "../entities/ennemy.hpp"
#include "../hud/menu/MainMenu.hpp"
#include "../hud/menu/PauseMenu.hpp"
#include "../hud/menu/OptionsMenu.hpp"
#include "../hud/menu/VideoMenu.hpp"
#include "../hud/menu/SoundMenu.hpp"
#include "../hud/menu/ControlMenu.hpp"

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
	};

private:
	sf::RenderWindow window;
	Player player;
	
	sf::View view;
	std::vector<Platform> platforms;
	Map gamemap;

	bool isRunning;
	bool isGamePaused;

	void addPlatform(float x, float y, float width, float height);
	void createWindow();
	void processEvents();
	void update();
	void render();
	void handleState(const sf::Event& event);
	void handleKeyboardInput(const sf::Event& event);

	GameState currentState;
	MainMenu mainMenu;
	PauseMenu pauseMenu;
	OptionsMenu optionsMenu;
	VideoMenu videoMenu;
	SoundMenu soundMenu;
	ControlMenu controlMenu;
};

#endif