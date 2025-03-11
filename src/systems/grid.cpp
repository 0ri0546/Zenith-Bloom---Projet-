#include "../systems/grid.hpp"

Grid::Grid()
{

	
}

void Grid::draw(sf::RenderWindow& window, Map& map)
{
	
}

void Grid::loadGrid(Map& map) {

	hauteur = map.getMap().size();
	cout << hauteur;
	largeur = map.getMap()[0].size();

	gridList = vector<vector<vector<int>>>(hauteur, vector<vector<int>>(largeur, vector<int>(largeur, 0)));
}