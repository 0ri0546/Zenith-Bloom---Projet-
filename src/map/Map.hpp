#ifndef MAP_H
#define MAP_H

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
	
	vector<sf::RectangleShape> recTab;
	vector<unique_ptr<Tiles>> tiles;
public:
	
	Map();
	~Map();

	vector<vector<char>> getMap();
	vector<unique_ptr<Tiles>>& getTiles();
	void draw(RenderWindow& window);

	void loadMap(int mapNum, vector<Ennemy>& ennemies);
	bool collideTiles(sf::FloatRect);
};


#endif // MAP_H