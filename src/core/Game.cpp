#include "Game.hpp"

Game::Game() : isRunning(false), currentState(GameState::MAIN_MENU), optionsMenu(OptionsMenu::MenuList::MAIN_MENU) {
	createWindow();
	view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	view.setCenter(player.getShape().getPosition());
}

void Game::addPlatform(float x, float y, float width, float height) {
	Platform temp(x, y, width, height);
	platforms.push_back(temp);
}

void Game::createWindow() {
	sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
	window.create(desktopMode, "Zenith Bloom", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);
	isRunning = true;
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			isRunning = false;
		}
		handleKeyboardInput(event);
		handleState(event);

		switch (currentState) {
		case GameState::MAIN_MENU:
			mainMenu.handleInput(window, event);
			break;
		case GameState::PAUSE_MENU:
			pauseMenu.handleInput(window, event);
			break;
		case GameState::OPTIONS_MENU:
			optionsMenu.handleInput(window, event);
			break;
		case GameState::VIDEO_MENU:
			videoMenu.handleInput(window, event);
			break;
		default:
			break;
		}
	}
}

void Game::update() {
	switch (currentState) {
	case GameState::PLAYING:
		player.update(platforms, window, view);
		view.setCenter(player.getShape().getPosition());
		break;
	default:
		view.setCenter(Config::WINDOW_WIDTH / 2, Config::WINDOW_HEIGHT / 2);
		window.setView(view);
		break;
	}
}

void Game::render() {
	window.clear(sf::Color::White);
	
	switch (currentState) {
	case GameState::MAIN_MENU:
		mainMenu.render(window);
		break;
	case GameState::PLAYING:
		window.draw(player.getShape());
		window.draw(player.getShapeAtk());
		window.draw(player.getShapeSmoke());
		window.draw(player.getShapeHUDEnergy());
		window.draw(player.getShapeFillEnergy());

		for (auto& platform : platforms) {
			window.draw(platform.getSprite());
		}

		window.setView(view);
		break;
	case GameState::PAUSE_MENU:
		pauseMenu.render(window);
		break;
	case GameState::OPTIONS_MENU:
		optionsMenu.render(window);
		break;
	case GameState::VIDEO_MENU:
		videoMenu.render(window);
		break;
	default:
		break;
	}

	window.display();
}

void Game::run() {
	addPlatform(-200, 400, 2000, 20);
	while (isRunning) {
		processEvents();
		update();
		render();
	}
}

void Game::handleState(const sf::Event& event) {
	switch (currentState) {
	case GameState::MAIN_MENU: {
		int result = mainMenu.handleInput(window, event);
		if (result == 1) { // Jouer
			currentState = GameState::PLAYING;
		}
		else if (result == 2) { // Options
			currentState = GameState::OPTIONS_MENU;
			optionsMenu.lastMenu = OptionsMenu::MenuList::MAIN_MENU;
		}
		else if (result == 3) { // Quitter
			isRunning = false;
			window.close();
		}
		break;
	}
	case GameState::PAUSE_MENU: {
		int result = pauseMenu.handleInput(window, event);
		if (result == 1) { // Reprendre
			currentState = GameState::PLAYING;
		}
		else if (result == 2) { // Options
			currentState = GameState::OPTIONS_MENU;
			optionsMenu.lastMenu = OptionsMenu::MenuList::PAUSE_MENU;
		}
		else if (result == 3) { // Menu Principal
			currentState = GameState::MAIN_MENU;
		}
		break;
	}
	case GameState::OPTIONS_MENU: {
		int result = pauseMenu.handleInput(window, event);
		if (result == 1) { // Retour
			if (optionsMenu.lastMenu == OptionsMenu::MenuList::MAIN_MENU) {
				currentState = GameState::MAIN_MENU;
			}
			else if (optionsMenu.lastMenu == OptionsMenu::MenuList::PAUSE_MENU) {
				currentState = GameState::PAUSE_MENU;
			}
		}
		else if (result == 2) { // Video
			currentState = GameState::VIDEO_MENU;
		}
		else if (result == 3) { // Son

		}
		else if (result == 4) { // Controles

		}
		break;
	}
	case GameState::VIDEO_MENU: {
		int result = videoMenu.handleInput(window, event);
		if (result == 1) { // Retour
			currentState = GameState::OPTIONS_MENU;
		}
		else if (result == 2) { // Plein Ecran
			videoMenu.toggleFullscreen(window);
			window.setView(sf::View(sf::FloatRect(0.f, 0.f, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y))));
		}
		break;
	}
	default:
		break;
	}
}

void Game::handleKeyboardInput(const sf::Event& event) {
	if (event.type == sf::Event::KeyPressed) {
		if (event.key.code == sf::Keyboard::Escape) {
			if (currentState == GameState::PLAYING) {
				currentState = GameState::PAUSE_MENU;
				isGamePaused = true;
			}
			else if (currentState == GameState::PAUSE_MENU) {
				currentState = GameState::PLAYING;
				isGamePaused = false;
			}
			else if (currentState == GameState::OPTIONS_MENU && optionsMenu.lastMenu == OptionsMenu::MenuList::PAUSE_MENU) {
				currentState = GameState::PLAYING;
				isGamePaused = false;
			}
		}
	}
}