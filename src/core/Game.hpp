#ifndef GAME_HPP
#define GAME_HPP

#include "../systems/Datas.hpp"
#include "../entities/Player.hpp"
#include "../map/Platform.hpp"
#include "../systems/AssetLoader.hpp"
#include "../map/Map.hpp"

class Game {
public:
	Game();
	void run();

private:
	sf::RenderWindow window;
	Player player;
	Platform platform;
	sf::View view;
	std::vector<Platform> platforms;
	Map gamemap;


	void addPlatform(float x, float y, float width, float height);
	void processEvents();
	void update();
	void render();
};

#endif