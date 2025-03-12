#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include "../systems/Datas.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "../map/Map.hpp"
#include "../hud/menu/MainMenu.hpp"
#include "../entities/FSM.hpp"
#include "../systems/grid.hpp"
#include "../systems/BouncingTitle.hpp"

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
		TITLE_MENU
	};

private:
	sf::RenderWindow window;
	Player player;
	//Player player2;
	//Ennemy ennemy;
	//Grid grid;
	
	//Grid grid = Grid(gamemap);
	

	sf::View view;
	std::vector<Platform> platforms;
	Map gamemap;
	Ennemy ennemy;
	void addPlatform(float x, float y, float width, float height);
	void processEvents(float deltaTime);
	void update(float deltaTime);
	void render();
	void handleState(const sf::Event& event, float deltaTime);
	GameState currentState;
	MainMenu mainMenu;

	BouncingTitle title;
	bool gameStarted = false;
	bool textFall;
};

#endif