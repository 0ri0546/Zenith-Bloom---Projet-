#include "Game.hpp"

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Zenith Bloom"), ennemy(50,50) {
	
	
	window.setFramerateLimit(60);
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(player.getShape().getPosition());

}

void Game::addPlatform(float x, float y, float width, float height) {
	Platform temp(x, y, width, height);
	platforms.push_back(temp);
	 
}

void Game::run() {
	
	

	gamemap.loadMap(1);
	//Assets assets();
	addPlatform(-1500, 350, 3000, 200);
	//addPlatform(60, 550, 40, 40);
	//addPlatform(0, 400, 200, 20);
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}
}

void Game::update() {

	player.update(platforms, window, view);
	view.setCenter(player.getShape().getPosition());
}

void Game::render() {
	window.clear();

	window.draw(player.getShape());
	window.draw(player.getShapeAtk());
	window.draw(player.getShapeSmoke());
	window.draw(player.getShapeHUDEnergy());
	window.draw(player.getShapeFillEnergy());
	window.draw(ennemy.getSprite());
	for (auto platform : platforms) {
		window.draw(platform.getSprite());
	}
	
	window.setView(view);

	window.display();
}