#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Map
{
private:

	int gridCellSize = 40;
	vector<vector<char>> map;
	
	vector<sf::RectangleShape> recTab;
public:
	Map();
	~Map();

	vector<vector<char>> getMap();

	void draw(RenderWindow& window);

	void loadMap(int mapNum);
};


#endif // MAP_H