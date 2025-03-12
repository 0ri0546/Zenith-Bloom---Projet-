#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../entities/FSM.hpp"

using namespace std;
using namespace sf;

class Map
{ 
private:

	int gridCellSize = 240;
	vector<vector<char>> map;
	
	vector<sf::RectangleShape> recTab;
public:
	
	Map();
	~Map();

	vector<vector<char>> getMap();

	void draw(RenderWindow& window);

	void loadMap(int mapNum, Ennemy& ennemy);
};


#endif // MAP_H