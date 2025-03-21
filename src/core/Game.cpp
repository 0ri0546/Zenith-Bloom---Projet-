#include "Game.hpp"

Game::Game() : isRunning(false), currentState(GameState::TITLE_MENU), optionsMenu(OptionsMenu::MenuList::MAIN_MENU), videoMenu(VideoMenu::MenuList::MAIN_MENU), title("Zenith Bloom", Shared::font), player(Shared::playerTexture) {
	createWindow();
	view.setSize(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y));
	
	gamemap.loadMap(2, ennemies, player, window, capsulesHP, capsulesEnergy, shadows);
	view.setCenter(player.getShape().getPosition());

	textFall = false;
	isDay = true; 
	isInTheSun = true;
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
		handleGamepadInput(deltaTime);

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
		case GameState::GAMEOVER_MENU:
			if (gameOverScreen.handleInput()) {
				currentState = GameState::MAIN_MENU;
				player.resetPlayer();
			}
			break;
		case GameState::LEVEL_SELECTOR_MENU:
			levelSelectMenu.handleInput(window, event);
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
	case GameState::SOUND_MENU:
		soundMenu.updateSliderValues();
		break;
	case GameState::VIDEO_MENU:
		videoMenu.update(window);
		break;
	case GameState::PLAYING:
		
		cycleDayNight();
		player.setTakingDamageBool(false);
		ennemies.erase(std::remove_if(ennemies.begin(), ennemies.end(), [](const unique_ptr<Ennemy>& e) { return e->currentState == DEAD; }), ennemies.end());
		
		player.update(gamemap.getTiles(), window, view, deltaTime, isDay, isInTheSun);
		player.fix(gamemap.getReparables());
		for (auto& ennemy : ennemies) {
			ennemy->runEnnemy(player, window, player.projectiles, ennemies, gamemap.getTiles(), deltaTime);
			auto& projectiles = ennemy->getProj();
			for (auto it = projectiles.begin(); it != projectiles.end();) {
				if (player.takeDamage(ennemy->getProjShape(*it), deltaTime)) {
					it = projectiles.erase(it);
				}
				else {
					++it;
				}
			}
		}

		if (ennemies.size() == 0) { player.setAnimationDamage = false; }
		for (auto it = capsulesEnergy.begin(); it != capsulesEnergy.end(); ) {
			if ((*it)->getSprite().getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
				player.augmenterEnergie((*it)->getEnergyValue());
				it = capsulesEnergy.erase(it);
			}
			else {
				++it;
			}
		}
		for (auto it = capsulesHP.begin(); it != capsulesHP.end(); ) {
			if ((*it)->getSprite().getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
				player.augmenterHP((*it)->getHPValue());
				it = capsulesHP.erase(it);
			}
			else {
				++it;
			}
		}
		for (auto it = player.projectiles.begin(); it != player.projectiles.end();) {
			bool erased = false;

			for (const auto& tile : gamemap.getTiles()) {
				if (it->getBounds().intersects(tile->getSprite().getGlobalBounds())) {
					it = player.projectiles.erase(it);
					erased = true;
					break;
				}
			}

			if (!erased) {
				++it;
			}
		}
		for (auto it = player.projectilesWater.begin(); it != player.projectilesWater.end();) {
			bool erased = false;

			for (const auto& tile : gamemap.getTiles()) {
				if (it->getBounds().intersects(tile->getSprite().getGlobalBounds())) {
					it = player.projectilesWater.erase(it);
					erased = true;
					break;
				}
			}

			if (!erased) {
				++it;
			}
		}
		for (auto& ennemy : ennemies) {
			auto& enemyProjectiles = ennemy->getProj();
			for (auto it = enemyProjectiles.begin(); it != enemyProjectiles.end();) {
				bool erased = false;

				for (const auto& tile : gamemap.getTiles()) {
					if (ennemy->getProjShape(*it).getGlobalBounds().intersects(tile->getSprite().getGlobalBounds())) {
						it = enemyProjectiles.erase(it);
						erased = true;
						break;
					}
				}
				if (!erased) {
					++it;
				}
			}
		}
		isInTheSun = false;
		for (auto& shadow : shadows) {
			if (player.getShape().getGlobalBounds().intersects(shadow->getGlobalBounds())) { 
				isInTheSun = false; 
				break;
			}
			else { isInTheSun = true; }
		}
		std::cout << isInTheSun << std::endl;

		view.setCenter(player.getShape().getPosition());
		if (player.getCanDisplayGameOverBool()) {
			currentState = GameState::GAMEOVER_MENU;
		}
		break;

	case GameState::EDITOR:
		gamemap.editormode(window, view);
		window.setView(view);
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
		gamemap.renderBackground(window);
		for (auto& tile : gamemap.getTiles()) {
			window.draw(tile->getSprite());
		}

		for (auto& ennemy : ennemies) {
			//window.draw(ennemy->circle);
			window.draw(ennemy->getSprite());
			
		}
		/*for (auto& flame : Incendiaire::flames) {
			window.draw(flame.getSprite());
		}*/
		/*for (auto& tank : Tanks) {
			window.draw(tank.getSprite());
		}*/
			//ennemy.runEnnemy(player, window, grid, TimeAstar);
		//cout << "Nombre d'ennemis : " << ennemies.size() << std::endl;

		for (int i = 0; i < ennemies.size(); i++) {
			//std::cout << ennemies[i].getSprite().getPosition().x << ", " << ennemies[i].getSprite().getPosition().x << std::endl;
		}
		for (auto proj : player.getProj()) {
			window.draw(player.getProjShape(proj));
		}
		for (auto proj : player.getProjWater()) {
			window.draw(player.getProjWaterShape(proj));
		}
		for (auto& ennemy : ennemies) {
			for (auto& proj : ennemy->getProj()) {
				window.draw(ennemy->getProjShape(proj));
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

		for (auto& item : capsulesEnergy) {
			window.draw(item->getSprite());
		}
		for (auto& item : capsulesHP) {
			window.draw(item->getSprite());
		}
		

		for (const auto& deco : gamemap.getDecos()) {
			window.draw(deco->getSprite());
		}
		for (const auto& reparable : gamemap.getReparables()) {
			window.draw(reparable->getSprite());
		}
		window.draw(player.getShapeSmoke());
		window.draw(player.getShape());
		for (const auto& tile : gamemap.getTiles()) {
			window.draw(tile->getSprite());
			window.draw(tile->getShadowShape());
		}

		for (auto& shadow : shadows) {
			window.draw(*shadow);
		}

		//----HUD----
		window.draw(player.getShapeFillEnergy());
		window.draw(player.getShapeFillHP());
		window.draw(player.getLifeBar2Sprite()); 
		window.draw(player.getEnergyBarSprite());
		window.draw(player.getShapeSurchauffe());
		window.draw(player.getSurchauffeBarSprite());
		if (isDay) { window.draw(player.getDaySprite()); }
		else { window.draw(player.getNightSprite()); }
		window.draw(player.getProgressBarSprite());
		//----HUD----
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
	case GameState::SOUND_MENU:
		soundMenu.render(window);
		break;
	case GameState::CONTROL_MENU:
		controlMenu.render(window);
		break;
	case GameState::GAMEOVER_MENU:
		gameOverScreen.render(window);
		break;
	case GameState::LEVEL_SELECTOR_MENU:
		levelSelectMenu.render(window);
		break;
	case GameState::EDITOR:
		gamemap.renderBackground(window);
		for (auto& tile : gamemap.getTiles()) {
			window.draw(tile->getSprite());
		}
		for (const auto& tile : gamemap.getTiles()) {
			window.draw(tile->getSprite());
			if (tile->hasShadow()) {
				window.draw(tile->getShadowShape());
			}
		}
		window.draw(gamemap.tempTile->getSprite());
		break;
	default:
		break;
	}
	
	window.display();
}

void Game::run() {
	sf::Clock clock;
	cycleClock.restart();
	AudioManager::getInstance().setSoundVolume("lv1", 30);
	AudioManager::getInstance().playSound("lv1");
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
		else if (result == 4) { // Editeur Mode
			currentState = GameState::EDITOR;
		}
		break;
	}
	case GameState::PAUSE_MENU: {
		int result = pauseMenu.handleInput(window, event);
		if (result == 1) { // Reprendre
			currentState = GameState::PLAYING;
			isGamePaused = false;
		}
		else if (result == 2) { // Options
			currentState = GameState::OPTIONS_MENU;
			optionsMenu.lastMenu = OptionsMenu::MenuList::PAUSE_MENU;
		}
		else if (result == 3) { // Menu Principal
			currentState = GameState::MAIN_MENU;
		}
		else if (result == 4) { // Editeur Mode
			currentState = GameState::EDITOR;
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
			if (!sf::Joystick::isConnected(0)) {
				currentState = GameState::CONTROL_MENU;
			}
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
	case GameState::LEVEL_SELECTOR_MENU: {
		int result = levelSelectMenu.handleInput(window, event);
		if (result == 1) { // Retour
			currentState = GameState::MAIN_MENU;
		}
		else if (result == 2) { // Level Tuto
			gamemap.loadMap(1, ennemies, player, window, capsulesHP, capsulesEnergy, shadows);
			player.resetPlayer();
			currentState = GameState::PLAYING;
		}
		else if (result == 3) { // Level 1
			gamemap.loadMap(2, ennemies, player, window, capsulesHP, capsulesEnergy, shadows);
			player.resetPlayer();
			currentState = GameState::PLAYING;
		}
		else if (result == 4) { // Level 2
			gamemap.loadMap(3, ennemies, player, window, capsulesHP, capsulesEnergy, shadows);
			player.resetPlayer();
			currentState = GameState::PLAYING;
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
			if (currentState == GameState::PLAYING || currentState == GameState::EDITOR) {
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

void Game::handleGamepadInput(float deltaTime) {
	if (sf::Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 7)) { // Start Button
			if (currentState == GameState::PLAYING) {
				currentState = GameState::PAUSE_MENU;
				isGamePaused = true;
			}
		}
	}
}

void Game::cycleDayNight() {
	if (cycleClock.getElapsedTime().asSeconds() >= 30.f && isDay) {
		cycleClock.restart();
		isDay = false;
	}if (cycleClock.getElapsedTime().asSeconds() >= 15.f && !isDay) {
		cycleClock.restart();
		isDay = true;
	}
}