#include"Map.hpp"
#include <fstream>
#include <iostream>
#include <string> 

Map::Map() {
    initBackground();
}

void Map::initBackground() {
    if (!backgroundTexture.loadFromFile("assets/maps/level2/zone_1/zone1_city_back.png")) {
        std::cerr << "Error loading texture! : background.png" << std::endl;
    }
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(0.5f, 0.5f);
    backgroundSprite.setColor(sf::Color(255, 255, 255));

    if (!backgroundTexture2.loadFromFile("assets/maps/level2/zone_1/zone1_city_front.png")) {
        std::cerr << "Error loading texture! : background.png" << std::endl;
    } 
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setScale(0.5f, 0.5f);
    backgroundSprite2.setColor(sf::Color(255, 255, 255));
    backgroundSprite2.setPosition(backgroundSprite.getPosition().x + backgroundSprite.getGlobalBounds().width, 0.f);

    if (!backgroundTexture3.loadFromFile("assets/maps/level2/zone_1/zone1_nature.png")) {
        std::cerr << "Error loading texture! : background.png" << std::endl;
    }
    backgroundSprite3.setTexture(backgroundTexture3);
    backgroundSprite3.setScale(0.5f, 0.5f);
    backgroundSprite3.setColor(sf::Color(255, 255, 255));
    backgroundSprite3.setPosition(backgroundSprite2.getPosition().x + backgroundSprite2.getGlobalBounds().width, 0.f);

    if (!backgroundTexture4.loadFromFile("assets/maps/tuto_tiles_4.png")) {
        std::cerr << "Error loading texture! : background.png" << std::endl;
    }
    backgroundSprite4.setTexture(backgroundTexture4);
    backgroundSprite4.setScale(0.5f, 0.5f);
    backgroundSprite4.setColor(sf::Color(255, 255, 255, 102));
    backgroundSprite4.setPosition(backgroundSprite3.getPosition().x + backgroundSprite3.getGlobalBounds().width, 0.f);
}

void Map::renderBackground(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(backgroundSprite2);
    window.draw(backgroundSprite3);
    window.draw(backgroundSprite4);
}

vector<vector<char>> Map::getMap() {
    return map;
}
 vector<unique_ptr<Tiles>>& Map::getTiles() {
    return tiles;
}
 vector<unique_ptr<Deco>>& Map::getDecos() {
     return decos;
 }
 vector<unique_ptr<Reparable>>& Map::getReparables() {
     return reparables;
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

void Map::preshowTile(int x, int y, sf::RenderWindow& window) {
    
    if (numtile < 103)
    {
        float posX = x * gridCellSize;
    float posY = y * gridCellSize;

    tempTile = std::make_unique<Tiles>(posX, posY, numtile);
    }
}

void Map::loadMap(int mapNum, vector<unique_ptr<Ennemy>>& ennemies, Player& player, sf::RenderWindow& window, vector<unique_ptr<CapsuleHP>>& capsulesHP, vector<unique_ptr<CapsuleEnergie>>& capsulesEnergie, vector<unique_ptr<Shadow>>& shadows) {
    map.clear();
    fond.clear();
    tiles.clear();
    decos.clear();
    reparables.clear();
    currentmap = mapNum;

    string path = "assets/maps/level" + to_string(mapNum) + "/map.txt";

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
                if (tileValue == 103) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 63));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 6));
                }
                if (tileValue == 104) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 63));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 33));
                }
                if (tileValue == 105) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 51));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 12));
                }
                if (tileValue == 106) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 63));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 32));
                }
                if (tileValue == 107) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 63));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 31));
                }
                if (tileValue == 108) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 63));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 30));
                }
                if (tileValue == 109) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 63));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 4));
                }
                if (tileValue == 110) {
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 51));
                    tiles.push_back(make_unique<Tiles>(i / 3 * gridCellSize, map.size() * gridCellSize, 10));
                }
                if (tileValue == 999) {
                    //Ennemy newEnnemy(i / 2 * gridCellSize, map.size() * gridCellSize);
                    ennemies.push_back(make_unique<Ennemy>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::ennemyTextureR, Shared::ennemyTexture, 135/* pas toucher*/, 178/* pas toucher*/, 120/*scaleX*/, 120/*scaleY*/, 190/*coliboxX*/, 190/*coliboxY*/)); // scale égaux obligatoire car carré 
                }
                if (tileValue == 998) {
                    /* Tank newEnnemy(i / 2 * gridCellSize, map.size() * gridCellSize);
                     Tankennemies.push_back(newEnnemy);*/
                    ennemies.push_back(make_unique<Tank>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::tankTexture, Shared::tankTextureR, 79, 131, 90, 120, 160, 160));
                }
                if (tileValue == 997) {
                    ennemies.push_back(make_unique<Drone>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::droneTexture, Shared::droneTexture, 139, 178, 270, 200, 64, 64));
                }
                if (tileValue == 996) {
                    ennemies.push_back(make_unique<Incendiaire>(i / 3 * gridCellSize, map.size() * gridCellSize, Shared::incendTexture, Shared::incendTextureR, 132, 80, 260, 140, 120, 100)); 
                }
                if (tileValue == 666) {
                    capsulesEnergie.push_back(make_unique<CapsuleEnergie>(15, Shared::capsuleEnergyTexture, i / 3 * gridCellSize, map.size() * gridCellSize));
                }
                if (tileValue == 667) {
                    capsulesHP.push_back(make_unique<CapsuleHP>(15, Shared::capsuleHPTexture, i / 3 * gridCellSize, map.size() * gridCellSize));
                }
                if (tileValue == 555) { /// ombre
                    shadows.push_back(make_unique<Shadow>(sf::Vector2f(120, 120), i / 3 * gridCellSize, map.size() * gridCellSize));
                }
            }
        }
        map.push_back(row);
    }
    file.close();

    // Load decors.txt
    ifstream decorsFile("assets/maps/level" + to_string(mapNum) + "/decors.txt");
    if (!decorsFile.is_open()) {
        cout << "Error: Decors file not found at " << "assets/maps/level" + to_string(mapNum) + "/decors.txt" << endl;
        return;
    }

    int rowIndex = 0;
    while (getline(decorsFile, line)) {
        for (size_t i = 0; i < line.size(); i += 3) {
            if (i + 2 >= line.size()) break;

            string decorCode = line.substr(i, 3);
            if (decorCode != "   ") {
                if (!isdigit(decorCode[0]) || !isdigit(decorCode[1]) || !isdigit(decorCode[2])) continue;

                int decorValue = stoi(decorCode);
                if (decorValue < 103) {
                    reparables.push_back(make_unique<Reparable>(i / 3 * 120, rowIndex * 120+60, decorValue));
                }
            }
        }
        rowIndex++;
    }
    decorsFile.close();
}

void Map::handleInput(sf::RenderWindow& window, sf::View& view) {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosWindow, view);
        int gridX = static_cast<int>(mousePosWorld.x) / gridCellSize;
        int gridY = static_cast<int>(mousePosWorld.y) / gridCellSize;
        modifyMapFile(gridX, gridY, numtile);
        if (numtile < 103)
        {
            supprTile(gridX * gridCellSize, gridY * gridCellSize);
            spawnTile(gridX * gridCellSize, gridY * gridCellSize, numtile);
        }

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
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) { if (inputOn == false) { numtile = 0; cout << numtile << endl; } inputOn = true; }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) { if (inputOn == false) { numtile = 555; cout << numtile << endl; } inputOn = true; }

    else { inputOn = false; }

    float moveSpeed = 10.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { view.move(0, -moveSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { view.move(-moveSpeed, 0); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) { view.move(0, moveSpeed); }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { view.move(moveSpeed, 0); }
}

void Map::modifyMapFile(int gridX, int gridY, int type) {
    string path = "assets/maps/level" + to_string(currentmap) + "/map.txt";
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
    sf::Vector2i mousePosWindow = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePosWindow, view);

    int gridX = static_cast<int>(mousePosWorld.x) / gridCellSize;
    int gridY = static_cast<int>(mousePosWorld.y) / gridCellSize;

    preshowTile(gridX, gridY, window);

    handleInput(window, view);
}

Map::~Map() {
    map.clear();
    fond.clear();
}