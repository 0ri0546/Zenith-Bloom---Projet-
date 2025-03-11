#pragma once

#include "SFML/Graphics.hpp"
#include "../systems/Datas.hpp"
#include <vector>
#include "../map/Map.hpp"

using namespace std;

class Grid {
private: 
	

	vector<vector<vector<int>>> grid; 
	//Map map; 

	int hauteur;
	int largeur;

public : 


	
	Grid();
	void draw(sf::RenderWindow& window, Map& map);
	void loadGrid(Map& map);


};