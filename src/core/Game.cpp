#include "Game.hpp"

Game::Game() : window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Zenith Bloom"), currentState(GameState::MAIN_MENU) {
	
	gamemap.loadMap(1, ennemy);
	
	window.setFramerateLimit(60);
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(player.getShape().getPosition());
	//grid.loadGrid(gamemap);
}

void Game::addPlatform(float x, float y, float width, float height) {
	Platform temp(x, y, width, height);
	platforms.push_back(temp);
}

void Game::run() {
	//gamemap.loadMap(1);
	//Assets assets();
	//addPlatform(0, 550, 40, 40);
	//addPlatform(60, 550, 40, 40);
	addPlatform(-200, 400, 2000, 20);
	//addPlatform(200, 0, 200, 500);
	sf::Clock clock;
	
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		
		processEvents();
		update(deltaTime);
		ennemy.runEnnemy(player, window, deltaTime);
		render();
	}
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window.close();
		}
		handleState(event);

		switch (currentState) {
		case GameState::MAIN_MENU:
			mainMenu.handleInput(window, event);
			break;
		default:
			break;
		}
	}
}

void Game::update(float deltaTime) {
	switch (currentState) {
	case GameState::PLAYING:
		player.update(platforms, window, view, deltaTime);
		view.setCenter(player.getShape().getPosition());
		break;
	default:
		break;
	}
}

void Game::render() {
	window.clear(sf::Color::Blue);
	
	switch (currentState) {
		
	case GameState::MAIN_MENU:
		mainMenu.render(window);
		break;
	case GameState::PLAYING:
		
		
		gamemap.draw(window);
		window.draw(player.getShape());
		window.draw(player.getShapeAtk());
		window.draw(player.getShapeSmoke());
		window.draw(player.getShapeHUDEnergy());
		window.draw(player.getShapeFillEnergy());
		
		ennemy.draw(window);
			//ennemy.runEnnemy(player, window, grid, TimeAstar);
			
		
		for (auto& platform : platforms) {
			window.draw(platform.getSprite());
		}

		window.setView(view);
		break;
	default:

		break;
	}

	window.display();
}


void Game::handleState(const sf::Event& event) {
	switch (currentState) {
	case GameState::MAIN_MENU:
		// Quand l'utilisateur choisit "Jouer"
		if (mainMenu.handleInput(window, event) == 1) {
			currentState = GameState::PLAYING;
		}
		break;
	default:
		break;
	}
}