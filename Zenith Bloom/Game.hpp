#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include "../systems/Datas.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "../map/Map.hpp"
#include "../entities/ennemy.hpp"

class Game {
public:
	Game();
	void run();

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
	void update();
	void render();
};

#endif