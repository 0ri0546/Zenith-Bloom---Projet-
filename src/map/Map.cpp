#include"Map.hpp"
#include <fstream>
#include <iostream>


Map::Map() {}

Map::~Map()
{
    map.clear();
}

vector<vector<char>> Map::getMap()
{
    return map;
}

void Map::draw(RenderWindow& window)
{
	for (auto grid : recTab)
	{
		window.draw(grid);
		
	}
}

void Map::loadMap(int mapNum, vector<Ennemy>& ennemies, Player& player, sf::RenderWindow& window)
{
    
    map.clear();
    string path = "assets/maps/map" + to_string(mapNum) + ".txt";

    ifstream file(path);
    if (!file.is_open())
    {
        cout << "Error: file not found" << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        vector<char> row;
        for (size_t i = 0; i < line.size(); i += 2)
        {
            if (i + 1 >= line.size())
            {
                cout << "Warning: Uneven characters in map file. Skipping last character." << endl;
                break;
            }

            string tileCode = line.substr(i, 2);
            if (!isdigit(tileCode[0]) || !isdigit(tileCode[1]))
            {
                cout << "Warning: Invalid tile code '" << tileCode << "' at position " << i << "." << endl;
                continue;
            }

            int tileValue;
            try
            {
                tileValue = stoi(tileCode);
            }
            catch (const std::invalid_argument& e)
            {
                cout << "Error: Invalid argument for stoi: " << tileCode << " at position " << i << "." << endl;
                continue;
            }
            catch (const std::out_of_range& e)
            {
                cout << "Error: Out of range argument for stoi: " << tileCode << " at position " << i << "." << endl;
                continue;
            }

            row.push_back(tileCode[0]);





            if (tileValue == 05)
            {

                recTab.push_back(sf::RectangleShape(sf::Vector2f(gridCellSize, gridCellSize)));
                recTab.back().setFillColor(sf::Color::White);
                recTab.back().setPosition( i / 2 * gridCellSize, map.size() * gridCellSize);
                
                
            }
            else if(tileValue == 04)
            {
                Ennemy newEnnemy(i / 2 * gridCellSize, map.size() * gridCellSize);
                ennemies.push_back(newEnnemy);
				newEnnemy.runEnnemy(player, window);
                recTab.push_back(sf::RectangleShape(sf::Vector2f(gridCellSize, gridCellSize)));
                recTab.back().setFillColor(sf::Color::White);
                recTab.back().setPosition(i / 2 * gridCellSize, map.size() * gridCellSize);
                
            }
            else
            {
                recTab.push_back(sf::RectangleShape(sf::Vector2f(gridCellSize, gridCellSize)));
                recTab.back().setFillColor(sf::Color::Black);
                recTab.back().setPosition(i / 2 * gridCellSize, map.size() * gridCellSize);
            }



        }
            map.push_back(row);
    }
		 
}
