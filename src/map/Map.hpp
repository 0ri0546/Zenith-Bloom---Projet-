#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "../entities/FSM.hpp"
#include "../entities/Tank.hpp"
#include "../entities/drone.hpp"
#include "../entities/incendiaire.hpp"
#include "../entities/CapsuleEnergie.hpp"
#include "../entities/CapsuleHP.hpp"
#include "../entities/Shadow.hpp"
#include "Deco.hpp"
#include "Reparable.hpp"

class Map { 
private:
	int gridCellSize = 120;
	int currentmap = 1;
	int numtile = 1;
	bool inputOn = false;

	vector<vector<char>> map;
	vector<vector<char>> fond;
	vector<unique_ptr<Tiles>> tiles;
	vector<unique_ptr<Deco>> decos;
	vector<unique_ptr<Reparable>> reparables;
	vector<sf::RectangleShape> recTab;
	sf::Sprite assetfull;

	sf::Texture backgroundTexture, backgroundTexture2, backgroundTexture3, backgroundTexture4;

public:
	Map();
	~Map();

	sf::Sprite backgroundSprite, backgroundSprite2, backgroundSprite3, backgroundSprite4;
	void renderBackground(sf::RenderWindow& window);

	vector<vector<char>> getMap();
	vector<unique_ptr<Tiles>>& getTiles();
	vector<unique_ptr<Deco>>& getDecos();
	vector<unique_ptr<Reparable>>& getReparables();
	std::unique_ptr<Tiles> tempTile;
	void spawnTile(int x, int y, int mapNum);
	void supprTile(int x, int y);
	void preshowTile(int x, int y, sf::RenderWindow& window);
	void editormode(sf::RenderWindow& window, sf::View& view);
	void handleInput(sf::RenderWindow& window, sf::View& view);
	void modifyMapFile(int griX, int gridY, int type);
	void initBackground();
	void loadDecors(int mapNum);
	void loadMap(int mapNum, vector<std::unique_ptr<Ennemy>>& ennemies, Player& player, sf::RenderWindow& window, vector<unique_ptr<CapsuleHP>>& capsulesHP, vector<unique_ptr<CapsuleEnergie>>& capsulesEnergie, vector<unique_ptr<Shadow>>& shadows);
};

#endif