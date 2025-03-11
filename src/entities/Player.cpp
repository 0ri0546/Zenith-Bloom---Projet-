#include "Player.hpp"

Player::Player() {
	Assets assets;
	playerSprite.setTexture(Shared::playerTexture);
	smokeSprite.setTexture(Shared::smokeTexture);
	swordSprite.setTexture(Shared::swordTexture);
	assets.resize(playerSprite, 50, 50);
	assets.resize(smokeSprite, 30, 50);
	assets.resize(swordSprite, 30, 50);

	velocityY = 0;
	gravity = 0.5f;
	isOnGround = false;

	jumpCount = maxJumps;
	canJump = true;

	lastDepIsLeft = false;

	energy = 100.f;
	maxJetpackEnergy = 100.f;
	jetpackPower = -3.f;
	energyConsumption = 10.f;
	energyRecharge = 1.f;

	shapeEnergy.setSize(sf::Vector2f(100, 30));
	shapeEnergy.setFillColor(sf::Color::Transparent);
	shapeEnergy.setOutlineColor(sf::Color::White);
	shapeEnergy.setOutlineThickness(2);
	shapeEnergy.setPosition(20, 20);

	damage = 15;
	hp = 100;
}

void Player::update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view, float deltaTime) {
	//reste à faire :
	//la fonction Player::boost() "le cyborg peut utiliser ses réacteurs pour se propulser en avant, ce qui consommera 15 points d'energie"
	//afficher les HUD (vie (coeurs ?), progression dans le niveau, etc...)

	//border();
	collide(platforms);
	//useJetpack();
	jump();
	deplacement(deltaTime);
	attack();
	//rangedAttack(window);
	//std::cout << "Nombre de projectiles : " << projectiles.size() << std::endl;

	updateHUDEnergy(view);
	std::cout << "deltatime : " << deltaTime << std::endl;
}

void Player::jump() {
	//reste à faire :

	if (!isOnGround) {
		velocityY += gravity;
	}
	else {
		jumpCount = maxJumps;
	}

	if (sf::Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 0) && jumpCount > 0 && canJump) {
			velocityY = -10.0f;
			jumpCount--;
			canJump = false;
			if (jumpCount == 0) {
				energy -= energyConsumption;
			}
		}
		if (!sf::Joystick::isButtonPressed(0, 0)) {
			canJump = true;
			if (energy < maxJetpackEnergy) {
				energy += energyRecharge;
			}
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpCount > 0 && canJump) {
			velocityY = -10.0f;
			jumpCount--;
			canJump = false;
			if (jumpCount == 0) {
				energy -= energyConsumption;
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			canJump = true;
			if (energy < maxJetpackEnergy) {
				energy += energyRecharge;
			}
		}
	}

	playerSprite.move(0, velocityY);

	if (jumpCount == 0) { //pour la fumée
		if (lastDepIsLeft) {
			smokeSprite.setPosition(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + 30);
		}
		else {
			smokeSprite.setPosition(playerSprite.getPosition().x - 30 + playerSprite.getGlobalBounds().width / 2, playerSprite.getPosition().y + 30);
		}
	}
	else {
		smokeSprite.setPosition(9999, 9999);
	}
}

void Player::collide(const std::vector<Platform>& platforms) { //collision joueur/platforms
	isOnGround = false;

	for (const auto& platform : platforms) {
		if (playerSprite.getGlobalBounds().intersects(platform.getSprite().getGlobalBounds())) {
			sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
			sf::FloatRect platformBounds = platform.getSprite().getGlobalBounds();

			float playerLeft = playerBounds.left;
			float playerRight = playerBounds.left + playerBounds.width;
			float playerTop = playerBounds.top;
			float playerBottom = playerBounds.top + playerBounds.height;

			float platformLeft = platformBounds.left;
			float platformRight = platformBounds.left + platformBounds.width;
			float platformTop = platformBounds.top;
			float platformBottom = platformBounds.top + platformBounds.height;

			if (velocityY > 0 && playerBottom > platformTop && playerTop < platformTop) { //bas
				isOnGround = true;
				velocityY = 0;
				playerSprite.setPosition(playerSprite.getPosition().x, platformTop - playerSprite.getGlobalBounds().height);
			}
			else if (velocityY < 0 && playerTop < platformBottom && playerBottom > platformBottom) { //haut
				velocityY = 0;
				playerSprite.setPosition(playerSprite.getPosition().x, platformBottom);
			}
			else if (playerRight > platformLeft && playerLeft < platformLeft && velocityY >= 0) { //gauche
				playerSprite.setPosition(platformLeft - playerBounds.width, playerSprite.getPosition().y);
			}
			else if (playerLeft < platformRight && playerRight > platformRight && velocityY >= 0) { //droite
				playerSprite.setPosition(platformRight, playerSprite.getPosition().y);
			}
		}
	}
	playerSprite.getGlobalBounds().width;
}

void Player::deplacement(float deltaTime) {
	deltaTime = std::min(deltaTime, 0.1f);

	const float acceleration = 1000.0f;
	const float friction = 1000.0f;
	const float maxSpeed = 700.0f; 
	float test = maxSpeed / 2;

	if (sf::Joystick::isConnected(0)) {
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 50) {
			velocityX += maxSpeed;
			lastDepIsLeft = false;
		}
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -50) {
			velocityX -= maxSpeed;
			lastDepIsLeft = true;
		}
	}
	else {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			velocityX += maxSpeed;
			lastDepIsLeft = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
			velocityX -= maxSpeed;
			lastDepIsLeft = true;
		}
	}

	if (velocityX > maxSpeed) velocityX = maxSpeed;
	if (velocityX < -maxSpeed) velocityX = -maxSpeed;

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::D) &&
		!sf::Keyboard::isKeyPressed(sf::Keyboard::Q) &&
		sf::Joystick::getAxisPosition(0, sf::Joystick::X) < 50 &&
		sf::Joystick::getAxisPosition(0, sf::Joystick::X) > -50) {

		if (velocityX > 0) {
			velocityX -= friction * deltaTime;
			if (velocityX < 0) velocityX = 0;
		}
		else if (velocityX < 0) {
			velocityX += friction * deltaTime;
			if (velocityX > 0) velocityX = 0;
		}
	}

	playerSprite.move(velocityX * deltaTime, 0);
}

void Player::border() {
	//reste à faire :
	//ajuster selon nos besoins
	if (playerSprite.getPosition().x <= 0) {
		playerSprite.setPosition(0, playerSprite.getPosition().y);
	}
	if (playerSprite.getPosition().x + playerSprite.getGlobalBounds().width >= Config::WINDOW_WIDTH) {
		playerSprite.setPosition(Config::WINDOW_WIDTH - playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
	}
}

float Player::attack() {
	float shortRangeDamage = 0.f;
	if (lastDepIsLeft) {
		swordSprite.setPosition(playerSprite.getPosition().x - 30, playerSprite.getPosition().y);
	}
	else {
		swordSprite.setPosition(playerSprite.getPosition().x + playerSprite.getGlobalBounds().width, playerSprite.getPosition().y);
	}

	if (attackClock.getElapsedTime().asSeconds() >= 0.5f) {

		if (sf::Joystick::isConnected(0)) {
			if (sf::Joystick::isButtonPressed(0, 2) && energy > 5.0) {
				shortRangeDamage = damage;
				energy -= 5.0;
				attackClock.restart();
				attackDurationClock.restart();
			}
		}
		else {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && energy > 5.0) {
				shortRangeDamage = damage;
				energy -= 5.0;
				attackClock.restart();
				attackDurationClock.restart();
			}
		}
	}

	if (attackDurationClock.getElapsedTime().asSeconds() >= 1.0f) { //valeur modifiable selon l'animation de l'attaque
		swordSprite.setPosition(9999, 9999);
	}

	return shortRangeDamage;
}

void Player::updateHUDEnergy(sf::View& view) {
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();

	float hudX = viewCenter.x - (viewSize.x / 2) + 20;
	float hudY = viewCenter.y - (viewSize.y / 2) + 20;

	shapeFillEnergy.setSize(sf::Vector2f((energy / maxJetpackEnergy) * 100, 30));
	shapeFillEnergy.setFillColor(sf::Color::Green);

	shapeEnergy.setPosition(hudX, hudY);
	shapeFillEnergy.setPosition(hudX, hudY);

}

sf::Sprite Player::getShape() const {
	return playerSprite;
}

sf::Sprite Player::getShapeAtk() const {
	return swordSprite;
}

sf::Sprite Player::getShapeSmoke() const {
	return smokeSprite;
}

sf::RectangleShape Player::getShapeHUDEnergy() const {
	return shapeEnergy;
}

sf::RectangleShape Player::getShapeFillEnergy() const {
	return shapeFillEnergy;
}