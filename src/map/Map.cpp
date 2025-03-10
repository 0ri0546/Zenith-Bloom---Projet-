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
}

void Map::loadMap(int mapNum)
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
                /*cout << "block 05" << endl;*/
            }
            map.push_back(row);
        }
    }
}