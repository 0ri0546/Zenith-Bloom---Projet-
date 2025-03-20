#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../entities/FSM.hpp"
#include "../entities/Tank.hpp"
#include "../entities/drone.hpp"
#include "../entities/incendiaire.hpp"


class Map { 
private:
	int gridCellSize = 120;
	int currentmap = 1;
	int numtile = 1;
	bool inputOn = false;

	vector<vector<char>> map;
	vector<unique_ptr<Tiles>> tiles;
	vector<sf::RectangleShape> recTab;
	sf::Sprite assetfull;

public:
	Map();
	~Map();

	vector<vector<char>> getMap();
	vector<unique_ptr<Tiles>>& getTiles();
	std::unique_ptr<Tiles> tempTile;
	void spawnTile(int x, int y, int mapNum);
	void supprTile(int x, int y);
	void preshowTile(int x, int y, sf::RenderWindow& window);
	void loadMap(int mapNum, vector<Ennemy>& ennemies, Player& player, sf::RenderWindow& window);
	void editormode(sf::RenderWindow& window, sf::View& view);
	void handleInput(sf::RenderWindow& window, sf::View& view);
	void modifyMapFile(int griX, int gridY, int type);

	void loadMap(int mapNum, vector<std::unique_ptr<Ennemy>>& ennemies, Player& player, sf::RenderWindow& window);
};

#endif