#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../entities/FSM.hpp"
#include "Tiles.hpp"

using namespace std;
using namespace sf;

class Map
{ 
private:

	int gridCellSize = 120;
	vector<vector<char>> map;
	int currentmap = 1;
	vector<sf::RectangleShape> recTab;
	vector<unique_ptr<Tiles>> tiles;
	int numtile = 1;
	Sprite assetfull;

	bool inputOn = false;
	
public:
	
	Map();
	~Map();

	vector<vector<char>> getMap();
	vector<unique_ptr<Tiles>>& getTiles();
	void spawnTile(int x, int y, int mapNum);
	void supprTile(int x, int y);
	void loadMap(int mapNum, vector<Ennemy>& ennemies, Player& player, sf::RenderWindow& window);
	void editormode(sf::RenderWindow& window, sf::View& view);
	void handleInput(sf::RenderWindow& window, sf::View& view);
	void modifyMapFile(int griX, int gridY, int type);

};




#endif // MAP_H