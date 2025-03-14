#include "Game.hpp"

Game::Game() : window(sf::VideoMode(Config::WINDOW_WIDTH, Config::WINDOW_HEIGHT), "Zenith Bloom"), currentState(GameState::PLAYING), title("Zenith Bloom", Shared::font) {
	//gamemap.loadMap(1); //pour l'instant ça fait bugger les collisions
	
	gamemap.loadMap(1, ennemies, player, window);
	
	window.setFramerateLimit(60);
	view.setSize(window.getSize().x, window.getSize().y);
	view.setCenter(player.getShape().getPosition());
	//grid.loadGrid(gamemap);

	textFall = false;
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
	addPlatform(700, 200, 500, 50);
	addPlatform(-200, 400, 2000, 50);
	addPlatform(-400, 600, 3000, 50);
	addPlatform(-200, 200, 500, 50);
	//addPlatform(700, 100, 500, 20);
	//addPlatform(200, 0, 200, 500);
	sf::Clock clock;
	
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		processEvents(deltaTime);
		update(deltaTime);
		render();
	}
}

void Game::processEvents(float deltaTime) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
			window.close();
		}
		handleState(event, deltaTime);

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
	case GameState::TITLE_MENU:
		title.update(deltaTime);
		if (textFall) {
			if (title.fallingText(deltaTime)) {
				currentState = GameState::MAIN_MENU;
			}
		}
		break;
	case GameState::MAIN_MENU:
		break;
	case GameState::PLAYING:
		player.update(platforms, window, view, deltaTime);
		for (auto& ennemy : ennemies) {
			ennemy.runEnnemy(player, window, player.projectiles, ennemies, platforms, deltaTime);
		}
		view.setCenter(player.getShape().getPosition());
		break;
	default:
		break;
	}
}

void Game::render() {
	window.clear(sf::Color::Blue);
	
	switch (currentState) {
	case GameState::TITLE_MENU:
		title.draw(window);
		break;

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
		
		for (auto& ennemy : ennemies) {
			window.draw(ennemy.getSprite());
		}
			//ennemy.runEnnemy(player, window, grid, TimeAstar);
		//cout << "Nombre d'ennemis : " << ennemies.size() << std::endl;

		for (int i = 0; i < ennemies.size(); i++)
		{
			//std::cout << ennemies[i].getSprite().getPosition().x << ", " << ennemies[i].getSprite().getPosition().x << std::endl;
		}
		
		for (auto& platform : platforms) {
			window.draw(platform.getSprite());
		}
		for (auto proj : player.getProj()) {
			window.draw(player.getProjShape(proj));
		}
		for (auto ennemy : ennemies) {
			for (auto proj : ennemy.getProj()) {
				window.draw(ennemy.getProjShape(proj));
			}
		}
		
		for (auto it = player.projectiles.begin(); it != player.projectiles.end();) {
			bool erased = false;

			for (auto& platform : platforms) {
				if (it->getBounds().intersects(platform.getSprite().getGlobalBounds())) {
					it = player.projectiles.erase(it);
					erased = true;
					break;
				}
			}

			if (!erased) {
				++it;
			}
		}

		window.setView(view);
		break;

	default:

		break;
	}

	window.display();
}

void Game::handleState(const sf::Event& event, float deltaTime) {
	switch (currentState) {
	case GameState::TITLE_MENU:
		if (title.canSkip) {
			if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 1))) {
				textFall = true;
			}
			else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
				textFall = true;
			}
		}
		
		break;
	case GameState::MAIN_MENU:
		if (mainMenu.handleInput(window, event) == 1) {
			currentState = GameState::PLAYING;
		}
		break;
	default:
		break;
	}
}

