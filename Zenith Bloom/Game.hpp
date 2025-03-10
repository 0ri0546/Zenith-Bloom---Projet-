#ifndef GAME_HPP
#define GAME_HPP
#pragma once

#include "Datas.hpp"
#include "Player.hpp"
#include "Platform.hpp"
#include "Map.hpp"
#include "AssetLoader.hpp"

class Game {
public:
	Game();
	void run();

private:
	sf::RenderWindow window;
	Player player;
	//Player player2;
	
	sf::View view;
	std::vector<Platform> platforms;
	Map gamemap;


	void addPlatform(float x, float y, float width, float height);
	void processEvents();
	void update();
	void render();
};

#endif