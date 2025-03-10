#include "Game.hpp"

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Zenith Bloom") {
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
	Assets assets();
	addPlatform(0, 550, 40, 40);
	//addPlatform(60, 550, 40, 40);
	addPlatform(-200, 400, 2000, 20);
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

	for (auto platform : platforms) {
		window.draw(platform.getSprite());
	}

	window.setView(view);

	window.display();
}