#include "Player.hpp"

Player::Player(sf::Texture& texture) : 
	jumpToLeftAnimation(Shared::playerReverseTexture, 194, 256, 3, 0.5f, 100, 100), // width height frames duration x y
	jumpToRightAnimation(texture, 194, 256, 3, 0.5f, 100, 100),
	walkToLeftAnimation(Shared::playerReverseTexture, 194, 256, 3, 0.2f, 100, 100), 
	walkToRightAnimation(texture, 194, 256, 3, 0.2f, 100, 100),
	staticToLeftAnimation(Shared::playerReverseTexture, 194, 256, 1, 0.5f, 100, 100),
	staticToRightAnimation(texture, 194, 256, 1, 0.5f, 100, 100),
	hangedToLefAnimation(Shared::playerReverseTexture, 194, 256, 3, 0.5f, 100, 100),
	hangedToRightAnimation(texture, 194, 256, 3, 0.5f, 100, 100),

	takeDamageToLeftAnimation(Shared::playerReverseTexture, 256, 256, 2, 0.5f, 100, 100),
	takeDamageToRightAnimation(texture, 256, 256, 2, 0.5f, 100, 100),
	deathToLeftAnimation(Shared::playerReverseTexture, 256, 256, 1, 0.5f, 100, 100),
	deathToRightAnimation(texture, 256, 256, 1, 0.5f, 100, 100),

	healAnimation(texture, 256, 256, 1, 0.5f, 100, 100),
	attackToLeftAnimation(Shared::playerReverseTexture, 275, 256, 4, 0.1f, 100, 100),
	attackToRightAnimation(texture, 275, 256, 4, 0.1f, 100, 100),
	rangedAttackAnimation(texture, 256, 256, 1, 0.5f, 100, 100),
	repairAnimation(texture, 256, 256, 1, 0.5f, 100, 100),

	smokeAnimation(Shared::smokeTexture, 350, 350, 11, 0.1f, 50, 50)
{
	playerSprite.setPosition(sf::Vector2f(400, 0));
	playerSprite.setTexture(texture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	swordSprite.setTexture(Shared::swordTexture);
	assets.resize(playerSprite, 100, 100);
	assets.resize(swordSprite, 30, 50);

	velocityY = 0;
	gravity = 1700.f;
	isOnGround = false;
	lastDepIsLeft = false;

	jumpCount = maxJumps;
	canJump = true;
	hangedToWallsLeft = false;
	hangedToWallsRight = false;
	depX = 0;
	bounce = 1000.f;
	jumpTime = 0.f;
	velocityX = 0.f;

	isAttacking = false;
	setAnimationDamage = false;	
	canAttack = true;
	takingDamage = false;

	energy = 100.f;
	maxJetpackEnergy = 100.f;
	jetpackPower = -3.f;
	energyConsumption = 10.f;
	energyRecharge = 1.f;

	shapeEnergy.setSize(sf::Vector2f(100, 30));
	shapeEnergy.setFillColor(sf::Color::Transparent);
	shapeEnergy.setOutlineColor(sf::Color::White);
	shapeEnergy.setOutlineThickness(2);
	
	hudEnergySprite.setTexture(Shared::progressBarTexture);
	assets.resize(hudEnergySprite, 100, 30);
	hudEnergySprite.setPosition(20, 20);

	damage = 15;
	hp = 100;
	vie = 3;

	daySprite.setTexture(Shared::dayTexture);
	assets.resize(daySprite, 40, 40);
	nightSprite.setTexture(Shared::nightTexture);
	assets.resize(nightSprite, 40, 40);
}

void Player::animate(float deltaTime) {
	// méthode pour animer le joueur
	if (setAnimationDamage) {                                           //---------------------takeDamage---------------------
		if (lastDepIsLeft) {
			takeDamageToLeftAnimation.update(deltaTime);
			takeDamageToLeftAnimation.applyToSprite(playerSprite, 2);
		}
		else {
			takeDamageToRightAnimation.update(deltaTime);
			takeDamageToRightAnimation.applyToSprite(playerSprite, 2);
		}
	}                                                                   //--------------------takeDamage---------------------
	else {
		if (velocityY < 100 && velocityY > -100) {                      //---------------------isOnGround---------------------
			if (!velocityX < 1 && !velocityX > -1) {                    //---------------------deplacement---------------------
				if (lastDepIsLeft) {
					walkToLeftAnimation.update(deltaTime);
					walkToLeftAnimation.applyToSprite(playerSprite, 0);
				}
				else {
					walkToRightAnimation.update(deltaTime);
					walkToRightAnimation.applyToSprite(playerSprite, 0);
				}
			}                                                           //---------------------deplacement---------------------
			else {                                                      //---------------------Static---------------------
				if (lastDepIsLeft) {
					staticToLeftAnimation.update(deltaTime);
					staticToLeftAnimation.applyToSprite(playerSprite, 1);
				}
				else {
					staticToRightAnimation.update(deltaTime);
					staticToRightAnimation.applyToSprite(playerSprite, 1);
				}
			}
		}                                                               //---------------------Static---------------------
		else {                                                          //---------------------Jump---------------------
			if (hangedToWallsLeft) {
				hangedToLefAnimation.update(deltaTime);
				hangedToLefAnimation.applyToSprite(playerSprite, 8);
			}
			else if (hangedToWallsRight) {
				hangedToRightAnimation.update(deltaTime);
				hangedToRightAnimation.applyToSprite(playerSprite, 8);
			}
			else {
				if (lastDepIsLeft) {
					jumpToLeftAnimation.update(deltaTime);
					jumpToLeftAnimation.applyToSprite(playerSprite, 8);
				}
				else {
					jumpToRightAnimation.update(deltaTime);
					jumpToRightAnimation.applyToSprite(playerSprite, 8);
				}
			}
		}                                                               //---------------------Jump---------------------
		if (isAttacking) {                                              //---------------------Atk---------------------
			if (lastDepIsLeft) {
				attackToLeftAnimation.update(deltaTime);
				attackToLeftAnimation.applyToSprite(playerSprite, 5);
			}
			else {
				attackToRightAnimation.update(deltaTime);
				attackToRightAnimation.applyToSprite(playerSprite, 5);
			}
		}                                                               //---------------------Atk---------------------
	}
	if (hp <= 0) {                                                      //---------------------Death-------------------
		if (lastDepIsLeft) {
			deathToLeftAnimation.update(deltaTime);
			deathToLeftAnimation.applyToSprite(playerSprite, 4);
		}
		else {
			deathToRightAnimation.update(deltaTime);
			deathToRightAnimation.applyToSprite(playerSprite, 4);
		}
	}                                                                   //---------------------Death-------------------
}

void Player::update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime) {
	// méthode pour mettre à jour le joueur
	animate(deltaTime);
	collide(tiles);
	jump(deltaTime);
	deplacement(deltaTime);
	attack(deltaTime);
	updateHUD(view);
	updateProjectiles(deltaTime, window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 5)) {
		rangedAttack();
	}
}

void Player::jump(float deltaTime) {
	// méthode pour gérer le saut du joueur (mouvement + fumée)
	deltaTime = std::min(deltaTime, 0.1f);
	if (!isOnGround && !hangedToWallsLeft && !hangedToWallsRight) {
		velocityY += gravity * deltaTime;
	}
	else {
		jumpCount = maxJumps;
	}

	if (hangedToWallsLeft || hangedToWallsRight) {
		jumpCount--;
	}

	if (sf::Joystick::isConnected(0)) {
		if (sf::Joystick::isButtonPressed(0, 0) && jumpCount > 0 && canJump) {
			velocityY = -10.0f / deltaTime;
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
			velocityY = -10.0f / deltaTime;
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
	playerSprite.move(0, velocityY * deltaTime);
	
	if (jumpCount == 0) {
		if (lastDepIsLeft) {
			smokeSprite.setPosition(playerSprite.getPosition().x + 50, playerSprite.getPosition().y + 100);
		}
		else {
			smokeSprite.setPosition(playerSprite.getPosition().x , playerSprite.getPosition().y + 100);
		}
		smokeAnimation.update(deltaTime);
		smokeAnimation.applyToSprite(smokeSprite, 0);
	}
	else {
		smokeSprite.setPosition(9999, 9999);
	}
}

void Player::collide(const std::vector<std::unique_ptr<Tiles>>& tiles) {
	// méthode pour gérer les collisions du joueur avec les plateformes
	isOnGround = false;
	hangedToWallsLeft = false;
	hangedToWallsRight = false;

	const float offsetTolerance = 3.f;
	const float groundTolerance = 5.f;

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

			
			if (velocityY >= 0 && playerBottom > platformTop && playerTop < platformTop + groundTolerance) { // bas
				isOnGround = true;
				velocityY = 0;
				playerSprite.setPosition(playerSprite.getPosition().x, platformTop - playerSprite.getGlobalBounds().height);
			}
			else if (playerRight > platformLeft && playerLeft < platformLeft + offsetTolerance) { //gauche
				playerSprite.setPosition(platformLeft - playerBounds.width, playerSprite.getPosition().y);
				if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 0)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					hangedToWallsLeft = true;
				}
			}
			else if (playerLeft < platformRight && playerRight > platformRight - offsetTolerance) { //droite
				playerSprite.setPosition(platformRight, playerSprite.getPosition().y);
				if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 0)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					hangedToWallsRight = true;
				}
			}
			else if (velocityY < 0 && playerTop < platformBottom && playerBottom > platformBottom - offsetTolerance) { //haut
				if (!hangedToWallsRight && !hangedToWallsLeft) {
					velocityY = 0;
					playerSprite.setPosition(playerSprite.getPosition().x, platformBottom);
				}
			}
		}
	}
}

void Player::deplacement(float deltaTime) {
	// méthode pour gérer le déplacement du joueur
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

float Player::attack(float deltaTime) {
	// méthode pour gérer l'attaque du joueur
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
		isAttacking = false;
	}
	else {
		isAttacking = true;
	}
	return shortRangeDamage;
}

void Player::updateHUD(sf::View& view) {
	// méthode pour mettre à jour l'interface utilisateur
	//------ENERGY------
	sf::Vector2f viewCenter = view.getCenter();
	sf::Vector2f viewSize = view.getSize();

	float hudX = viewCenter.x - (viewSize.x / 2) + 20;
	float hudY = viewCenter.y - (viewSize.y / 2) + 20;

	shapeFillEnergy.setSize(sf::Vector2f((energy / maxJetpackEnergy) * 100, 30));
	shapeFillEnergy.setFillColor(sf::Color::Green);

	hudEnergySprite.setPosition(hudX, hudY);
	shapeFillEnergy.setPosition(hudX, hudY);
	//------ENERGY------
	//------DAY/NIGHT------
	daySprite.setPosition(viewCenter.x + viewSize.x / 2 - 60, viewCenter.y - viewSize.y / 2 + 20);
	nightSprite.setPosition(viewCenter.x + viewSize.x / 2 - 60, viewCenter.y - viewSize.y / 2 + 20);
	//------DAY/NIGHT------
}

void Player::rangedAttack() {
	// méthode pour gérer l'attaque à distance du joueur
	if (rangedAttackClock.getElapsedTime().asSeconds() >= 0.3f && energy > 10.0f) {
		sf::Vector2f spawnPos = playerSprite.getPosition();
		spawnPos.x += lastDepIsLeft ? -20 : playerSprite.getGlobalBounds().width;
		Projectile newProjectile(Shared::projectileTexture, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
		newProjectile.resize(30, 30);
		projectiles.push_back(newProjectile);
		energy -= 10.0f;
		rangedAttackClock.restart();
	}
}

void Player::updateProjectiles(float deltaTime, sf::RenderWindow& window) {
	// méthode pour mettre à jour les projectiles du joueur
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->update(deltaTime);
		++it;
	}
}

bool Player::takeDamage(sf::Sprite projEnnemi, float deltaTime) {
	// méthode pour gérer les dégâts infligés au joueur
	if (playerSprite.getGlobalBounds().intersects(projEnnemi.getGlobalBounds())) {
		takeDamageClock.restart();
		hp--;
		takingDamage = true;
		setAnimationDamage = true;
	}

	if (takeDamageClock.getElapsedTime().asSeconds() > 0.5) {
		setAnimationDamage = false;
	}

	return takingDamage;
}

//getters/setters
sf::Sprite Player::getShape() const { return playerSprite; }
sf::Sprite Player::getShapeAtk() const { return swordSprite; }
sf::Sprite Player::getShapeSmoke() const { return smokeSprite; }
sf::Sprite Player::getSpriteHUDEnergy() const { return hudEnergySprite; }
sf::RectangleShape Player::getShapeFillEnergy() const { return shapeFillEnergy; }
std::vector<Projectile> Player::getProj() const { return projectiles; }
sf::Sprite Player::getProjShape(Projectile& proj) const { return proj.getSprite(); }
sf::Sprite Player::getDaySprite() const { return daySprite; }
sf::Sprite Player::getNightSprite() const { return nightSprite; }
bool Player::getTakingDamageBool() const { return takingDamage; }
void Player::setTakingDamageBool(bool takingDamage) { this->takingDamage = takingDamage; }

Player::~Player() {
	projectiles.clear();
}