#include "Game.hpp"

Game::Game() : isRunning(false), currentState(GameState::MAIN_MENU), optionsMenu(OptionsMenu::MenuList::MAIN_MENU), videoMenu(VideoMenu::MenuList::MAIN_MENU), title("Zenith Bloom", Shared::font) {
	createWindow();
	view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	
	gamemap.loadMap(1, ennemies, player, window);
	view.setCenter(player.getShape().getPosition());
	//grid.loadGrid(gamemap);

	textFall = false;
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

void Game::processEvents(float deltaTime) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
			isRunning = false;
		}
		handleKeyboardInput(event);
		handleState(event, deltaTime);

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
		case GameState::SOUND_MENU:
			soundMenu.handleInput(window, event);
			break;
		case GameState::CONTROL_MENU:
			controlMenu.handleInput(window, event);
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
		player.update(gamemap.getTiles(), window, view, deltaTime);
		for (auto& ennemy : ennemies) {
			ennemy.runEnnemy(player, window, player.projectiles, ennemies, gamemap.getTiles(), deltaTime);
		}
		view.setCenter(player.getShape().getPosition());
		break;
	default:
		view.setCenter(static_cast<float>(Config::WINDOW_WIDTH) / 2.f, static_cast<float>(Config::WINDOW_HEIGHT) / 2.f);
		window.setView(view);
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
	case GameState::PAUSE_MENU:
		pauseMenu.render(window);
		break;
	case GameState::OPTIONS_MENU:
		optionsMenu.render(window);
		break;
	case GameState::VIDEO_MENU:
		videoMenu.render(window);
		videoMenu.renderSlider(window);
		break;
	case GameState::SOUND_MENU:
		soundMenu.render(window);
		soundMenu.renderSliders(window);
		break;
	case GameState::CONTROL_MENU:
		controlMenu.render(window);
		break;
	default:

		break;
	}

	window.display();
}

void Game::run() {
	//gamemap.loadMap(1);
	//Assets assets();
	//addPlatform(0, 550, 40, 40);
	//addPlatform(60, 550, 40, 40);
	addPlatform(-200, 400, 2000, 20);
	//addPlatform(200, 0, 200, 500);
	sf::Clock clock;
	
	while (isRunning) {
		float deltaTime = clock.restart().asSeconds();
		processEvents(deltaTime);
		update(deltaTime);
		render();
	}
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
		int result = optionsMenu.handleInput(window, event);
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
			currentState = GameState::SOUND_MENU;
		}
		else if (result == 4) { // Controles
			currentState = GameState::CONTROL_MENU;
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
		else if (result == 3) { // VSync
			videoMenu.toggleVSync(window);
		}
		break;
	}
	case GameState::SOUND_MENU: {
		int result = soundMenu.handleInput(window, event);
		if (result == 1) { // Retour
			currentState = GameState::OPTIONS_MENU;
		}
		break;
	}
	case GameState::CONTROL_MENU: {
		int result = controlMenu.handleInput(window, event);
		if (result == 1) { // Retour
			currentState = GameState::OPTIONS_MENU;
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
			else if (currentState == GameState::OPTIONS_MENU && optionsMenu.lastMenu == OptionsMenu::MenuList::MAIN_MENU) {
				currentState = GameState::MAIN_MENU;
			}
			else if (currentState == GameState::OPTIONS_MENU && optionsMenu.lastMenu == OptionsMenu::MenuList::PAUSE_MENU) {
				currentState = GameState::PAUSE_MENU;
			}
			else if (currentState == GameState::VIDEO_MENU) {
				currentState = GameState::OPTIONS_MENU;
			}
			else if (currentState == GameState::SOUND_MENU) {
				currentState = GameState::OPTIONS_MENU;
			}
			else if (currentState == GameState::CONTROL_MENU) {
				currentState = GameState::OPTIONS_MENU;
			}
		}
	}
}
