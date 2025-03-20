#include"Map.hpp"
#include <fstream>
#include <iostream>
#include <string> 

Map::Map() {}

vector<vector<char>> Map::getMap() {
    return map;
}
 vector<unique_ptr<Tiles>>& Map::getTiles() {
    return tiles;
}

 void Map::spawnTile(int x, int y, int mapNum) {
     tiles.push_back(make_unique<Tiles>(x, y, mapNum));
}

 void Map::supprTile(int x, int y) {
     for (auto it = tiles.begin(); it != tiles.end(); ++it) {

         if ((*it)->getSprite().getPosition().x == x && (*it)->getSprite().getPosition().y == y) {
             tiles.erase(it);
             break;
         }
     }
 }

void Map::loadMap(int mapNum, vector<unique_ptr<Ennemy>>& ennemies, Player& player, sf::RenderWindow& window) {
    map.clear();
    tiles.clear();
    currentmap = mapNum;

    string path = "assets/maps/map" + to_string(mapNum) + ".txt";
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: file not found" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        vector<char> row;
        for (size_t i = 0; i < line.size(); i += 3) {
            if (i + 1 >= line.size()) {
                cout << "Warning: Uneven characters in map file. Skipping last character." << endl;
                break;
            }

            string tileCode = line.substr(i, 3);
            if (tileCode != "   ") {
                if (!isdigit(tileCode[0]) || !isdigit(tileCode[1]) || !isdigit(tileCode[2])) {
                    cout << "Warning: Invalid tile code '" << tileCode << "' at position " << i << "." << endl;
                    continue;
                }

                int tileValue;
                tileValue = stoi(tileCode);

                row.push_back(tileCode[0]);

                if (tileValue < 102) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, tileValue));
                }
                if (tileValue == 14) {
                    //Ennemy newEnnemy(i / 2 * gridCellSize, map.size() * gridCellSize);
                    ennemies.push_back(make_unique<Ennemy>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::ennemyTexture, Shared::tankTextureR, 139/* pas toucher*/, 178/* pas toucher*/, 80/*scaleX*/, 80/*scaleY*/, 150/*coliboxX*/, 150/*coliboxY*/)); // scale égaux obligatoire car carré 
                }
                if (tileValue == 15) {
                    /* Tank newEnnemy(i / 2 * gridCellSize, map.size() * gridCellSize);
                     Tankennemies.push_back(newEnnemy);*/
                    ennemies.push_back(make_unique<Tank>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::tankTexture, Shared::tankTextureR, 79, 131, 90, 120, 160, 160));
                }
                if (tileValue == 16) {
                    ennemies.push_back(make_unique<Drone>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::droneTexture, Shared::tankTextureR, 139, 178, 60, 60, 64, 64));
                }
                if (tileValue == 17) {
                    ennemies.push_back(make_unique<Incendiaire>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::incendTexture, Shared::incendTextureR, 132, 80, 120, 70, 80, 60)); // scale avec dif de 50 = perfect 
                }
            }
        }
        map.push_back(row);
    }
}

void Map::handleInput(sf::RenderWindow& window, sf::View& view) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosWindow, view);
        int gridX = static_cast<int>(mousePosWorld.x) / gridCellSize;
        int gridY = static_cast<int>(mousePosWorld.y) / gridCellSize;
        modifyMapFile(gridX, gridY, numtile);
        supprTile(gridX * gridCellSize, gridY * gridCellSize);
        spawnTile(gridX * gridCellSize, gridY * gridCellSize, numtile);

    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosWindow, view);
        int gridX = static_cast<int>(mousePosWorld.x) / gridCellSize;
        int gridY = static_cast<int>(mousePosWorld.y) / gridCellSize;
        modifyMapFile(gridX, gridY, -1);
        supprTile(gridX * gridCellSize, gridY * gridCellSize);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { if (inputOn == false) { numtile += 1; cout << numtile << endl;    } inputOn = true; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { if (inputOn == false) { numtile -= 1; cout << numtile << endl;    } inputOn = true; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { if (inputOn == false) { numtile -= 10; cout << numtile << endl;    } inputOn = true; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { if (inputOn == false) { numtile += 10; cout << numtile << endl;    } inputOn = true; }
    else { inputOn = false; }

    float moveSpeed = 10.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { view.move(0, -moveSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { view.move(-moveSpeed, 0); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { view.move(0, moveSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { view.move(moveSpeed, 0); }
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

    vector<string> lines;
    while (getline(file, line)) {
        lines.push_back(line);
    }

    if (gridY >= 0 && gridY < lines.size()) {
        string& lineToModify = lines[gridY];

        int startIdx = gridX * 3;
        if (type == -1) {
            if (startIdx + 2 < lineToModify.size()) {
                lineToModify[startIdx] = ' ';
                lineToModify[startIdx + 1] = ' ';
                lineToModify[startIdx + 2] = ' ';
            }
        }
        else {
            if (startIdx + 2 < lineToModify.size()) {
                lineToModify[startIdx] = type / 100 + '0';
                lineToModify[startIdx + 1] = (type % 100) / 10 + '0';
                lineToModify[startIdx + 2] = type % 10 + '0';
            }
        }
    }

    file.close();
    ofstream outFile(path, ios::out);
    if (!outFile.is_open()) {
        cout << "Error: Unable to open map file for writing." << endl;
        return;
    }

    for (const auto& modifiedLine : lines) {
        outFile << modifiedLine << endl;
    }

    outFile.close(); 
}

void Map::editormode(sf::RenderWindow& window, sf::View& view) {
    handleInput(window, view);
}

Map::~Map() {
    map.clear();
}