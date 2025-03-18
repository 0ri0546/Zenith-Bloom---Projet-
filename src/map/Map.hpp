#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../entities/FSM.hpp"
#include "../entities/Tank.hpp"
#include "../entities/drone.hpp"
#include "../entities/incendiaire.hpp"



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

	void loadMap(int mapNum, vector<std::unique_ptr<Ennemy>>& ennemies, Player& player, sf::RenderWindow& window);
};


#endif // MAP_H