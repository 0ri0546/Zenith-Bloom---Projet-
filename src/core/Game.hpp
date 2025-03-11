#ifndef GAME_HPP
#define GAME_HPP

#include "../systems/Datas.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "../map/Map.hpp"
#include "../hud/menu/MainMenu.hpp"
#include "../entities/ennemy.hpp"
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
		GAMEOVER_MENU,
		VICTORY_MENU,
	};

private:
	sf::RenderWindow window;
	Player player;
	//Player player2;
	Ennemy ennemy;

	sf::View view;
	std::vector<Platform> platforms;
	Map gamemap;

	void addPlatform(float x, float y, float width, float height);
	void processEvents();
	void update(float deltaTime);
	void render();
	void handleState(const sf::Event& event);

	GameState currentState;
	MainMenu mainMenu;
};

#endif