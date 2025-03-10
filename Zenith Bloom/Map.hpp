#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Map
{
private:

	vector<vector<char>> map;

public:
	Map();
	~Map();

	vector<vector<char>> getMap();

	void draw(RenderWindow& window);

	void loadMap(int mapNum);
};


#endif // MAP_H