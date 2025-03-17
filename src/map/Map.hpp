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
	int currentmap;
	vector<sf::RectangleShape> recTab;
	vector<unique_ptr<Tiles>> tiles;
	
public:
	
	Map();
	~Map();

	vector<vector<char>> getMap();
	vector<unique_ptr<Tiles>>& getTiles();

	void loadMap(int mapNum, vector<Ennemy>& ennemies, Player& player, sf::RenderWindow& window);

	void handleInput(sf::RenderWindow& window, sf::View& view);
	void modifyMapFile(int griX, int gridY, int type);

};




#endif // MAP_H