#include "Player.hpp"

Player::Player() {
	playerSprite.setPosition(sf::Vector2f(400, 0));

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
	hangedToWallsLeft = false;
	hangedToWallsRight = false;
	depX = 0;
	bounce = 1000.f;
	jumpTime = 0.f;
	velocityX = 0.f;

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
	vie = 3;
}

void Player::update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime) {
	//reste à faire :
	//afficher les HUD (vie (coeurs ?), progression dans le niveau, etc...)

	//border();
	collide(tiles);
	//useJetpack();
	jump(deltaTime);
	deplacement(deltaTime);
	attack();
	//rangedAttack(window);
	//std::cout << "Nombre de projectiles : " << projectiles.size() << std::endl;

	updateHUDEnergy(view);
	//std::cout << "deltatime : " << deltaTime << std::endl;

	updateProjectiles(deltaTime, window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 5)) {
		rangedAttack();
	}
	std::cout << "hp : " << hp << std::endl;
}

void Player::jump(float deltaTime) {
	//reste à faire :

	if (!isOnGround && !hangedToWallsLeft && !hangedToWallsRight) {
		velocityY += gravity;
	}
	else {
		jumpCount = maxJumps;
	}

	if (hangedToWallsLeft || hangedToWallsRight) {
		jumpCount--;
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
		if (sf::Keyboard::isKeyPressed(Keybind::getKey(Keybind::Action::Jump)) && jumpCount > 0 && canJump) {
			velocityY = -10.0f;
			jumpCount--;
			canJump = false;
			if (jumpCount == 0) {
				energy -= energyConsumption;
			}
		}
		if (!sf::Keyboard::isKeyPressed(Keybind::getKey(Keybind::Action::Jump))) {
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

void Player::collide(const std::vector<std::unique_ptr<Tiles>>& tiles) {
	isOnGround = false;
	hangedToWallsLeft = false;
	hangedToWallsRight = false;

	for (const auto& tile : tiles) {
		if (playerSprite.getGlobalBounds().intersects(tile->getSprite().getGlobalBounds())) {
			sf::FloatRect playerBounds = playerSprite.getGlobalBounds();
			sf::FloatRect platformBounds = tile->getSprite().getGlobalBounds();

			float playerLeft = playerBounds.left;
			float playerRight = playerBounds.left + playerBounds.width;
			float playerTop = playerBounds.top;
			float playerBottom = playerBounds.top + playerBounds.height;

			float platformLeft = platformBounds.left;
			float platformRight = platformBounds.left + platformBounds.width;
			float platformTop = platformBounds.top;
			float platformBottom = platformBounds.top + platformBounds.height;

			if (velocityY > 0 && playerBottom > platformTop && playerTop < platformTop) { // bas
				isOnGround = true;
				velocityY = 0;
				playerSprite.setPosition(playerSprite.getPosition().x, platformTop - playerSprite.getGlobalBounds().height);
			}
			else if (playerRight > platformLeft && playerLeft < platformLeft) { // gauche
				playerSprite.setPosition(platformLeft - playerBounds.width, playerSprite.getPosition().y);
				if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 0)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					hangedToWallsLeft = true;
				}
				
			}
			else if (playerLeft < platformRight && playerRight > platformRight) { // droite
				playerSprite.setPosition(platformRight, playerSprite.getPosition().y);
				if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 0)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					hangedToWallsRight = true;
				}
				
			}
			else if (velocityY < 0 && playerTop < platformBottom && playerBottom > platformBottom) { // haut
				if (!hangedToWallsRight && !hangedToWallsLeft)
				{
					velocityY = 0;
					playerSprite.setPosition(playerSprite.getPosition().x, platformBottom);
				}
				
			}

		}
	}
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
		if (sf::Keyboard::isKeyPressed(Keybind::getKey(Keybind::Action::MoveRight))) {
			velocityX += maxSpeed;
			lastDepIsLeft = false;
		}
		if (sf::Keyboard::isKeyPressed(Keybind::getKey(Keybind::Action::MoveLeft))) {
			velocityX -= maxSpeed;
			lastDepIsLeft = true;
		}
	}

	if (velocityX > maxSpeed) velocityX = maxSpeed;
	if (velocityX < -maxSpeed) velocityX = -maxSpeed;

	if (!sf::Keyboard::isKeyPressed(Keybind::getKey(Keybind::Action::MoveRight)) &&
		!sf::Keyboard::isKeyPressed(Keybind::getKey(Keybind::Action::MoveLeft)) &&
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
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && energy > 5.0) {
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

void Player::rangedAttack() {
	if (rangedAttackClock.getElapsedTime().asSeconds() >= 0.3f && energy > 10.0f) {
		sf::Vector2f spawnPos = playerSprite.getPosition();
		spawnPos.x += lastDepIsLeft ? -20 : playerSprite.getGlobalBounds().width;

		Projectile newProjectile(Shared::projectileTexture, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
		newProjectile.resize(20, 20);

		projectiles.push_back(newProjectile);

		energy -= 10.0f;
		rangedAttackClock.restart();
	}
}

void Player::updateProjectiles(float deltaTime, sf::RenderWindow& window) {
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->update(deltaTime);
		++it;
	}
}

bool Player::takeDamage(sf::Sprite projEnnemi) {
	if (playerSprite.getGlobalBounds().intersects(projEnnemi.getGlobalBounds())) {
		hp--;
		return true;
	}
	return false;
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
std::vector<Projectile> Player::getProj() const {
	return projectiles;
}

sf::Sprite Player::getProjShape(Projectile& proj) const {
	return proj.getSprite();
}

Player::~Player() {
	projectiles.clear();
}