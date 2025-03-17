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
 vector<unique_ptr<Tiles>>& Map::getTiles()
{
    return tiles;
}


void Map::loadMap(int mapNum, vector<Ennemy>& ennemies, Player& player, sf::RenderWindow& window)
{
    
    map.clear();
    tiles.clear();
    currentmap = mapNum;
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
        for (size_t i = 0; i < line.size(); i += 3)
        {
            if (i + 1 >= line.size())
            {
                cout << "Warning: Uneven characters in map file. Skipping last character." << endl;
                break;
            }

            string tileCode = line.substr(i, 3);
            if(tileCode != "   ")
            {
                if (!isdigit(tileCode[0]) || !isdigit(tileCode[1]) || !isdigit(tileCode[2]))
                {
                    cout << "Warning: Invalid tile code '" << tileCode << "' at position " << i << "." << endl;
                    continue;
                }

                int tileValue;
                tileValue = stoi(tileCode);

                row.push_back(tileCode[0]);



                if (tileValue < 102) {

                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, tileValue));
                }
                if (tileValue == 999)
                {
                    Ennemy newEnnemy(i / 3 * gridCellSize, map.size() * gridCellSize);
                    ennemies.push_back(newEnnemy);
                }
            }
        }
            map.push_back(row);
    }
}

void Map::handleInput(sf::RenderWindow& window, sf::View& view) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosWindow, view);
        int gridX = static_cast<int>(mousePosWorld.x) / gridCellSize;
        int gridY = static_cast<int>(mousePosWorld.y) / gridCellSize;
        modifyMapFile(gridX, gridY, 4);
    }
}

void Map::modifyMapFile(int gridX, int gridY, int type) {
    string path = "assets/maps/map" + to_string(currentmap) + ".txt";

    fstream file(path, ios::in | ios::out);
    if (!file.is_open()) {
        cout << "Error: Unable to open map file." << endl;
        return;
    }

    string line;
    int rowIndex = 0;
    long pos = 0; 

    while (getline(file, line)) {
        if (rowIndex == gridY) {
            int startIdx = gridX * 3;

            if (startIdx + 2 < line.size()) {
                line[startIdx] = '0';
                line[startIdx + 1] = '0';
                line[startIdx + 2] = '4';

                file.seekp(pos, ios::beg);

                file << line << endl;
                break; 
            }
        }
        pos = file.tellg();
        rowIndex++;
    }

    file.close();
}

