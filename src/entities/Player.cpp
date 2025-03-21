#include "Player.hpp"

Player::Player(sf::Texture& texture) : 
	jumpToLeftAnimation(Shared::playerReverseTexture, 194, 256, 3, 0.5f, 100, 100), // width height frames duration x y
	jumpToRightAnimation(texture, 194, 256, 3, 0.5f, 100, 100),
	walkToLeftAnimation(Shared::playerReverseTexture, 194, 256, 3, 0.2f, 100, 100), 
	walkToRightAnimation(texture, 194, 256, 3, 0.2f, 100, 100),
	staticToLeftAnimation(Shared::playerReverseTexture, 194, 256, 1, 0.5f, 100, 100),
	staticToRightAnimation(texture, 194, 256, 1, 0.2f, 100, 100),
	hangedToLefAnimation(Shared::playerReverseTexture, 194, 256, 3, 0.5f, 100, 100),
	hangedToRightAnimation(texture, 194, 256, 3, 0.2f, 100, 100),

	takeDamageToLeftAnimation(Shared::playerReverseTexture, 194, 256, 2, 0.5f, 100, 100),
	takeDamageToRightAnimation(texture, 194, 256, 2, 0.5f, 100, 100),
	deathToLeftAnimation(Shared::playerReverseTexture, 257, 256, 6, 0.3f, 100, 100),
	deathToRightAnimation(texture, 257, 256, 6, 0.3f, 100, 100),

	healAnimation(texture, 256, 256, 1, 0.5f, 100, 100),
	attackToLeftAnimation(Shared::playerReverseTexture, 275, 256, 4, 0.1f, 100, 100),
	attackToRightAnimation(texture, 275, 256, 4, 0.1f, 100, 100),
	rangedAttackToLeftAnimation(Shared::playerReverseTexture, 310, 256, 4, 0.3f, 100, 100),
	rangedAttackToRightAnimation(texture, 310, 256, 4, 0.3f, 100, 100),
	repairToLeftAnimation(Shared::playerReverseTexture, 256, 256, 5, 0.3f, 100, 100),
	repairToRightAnimation(texture, 256, 256, 5, 0.3f, 100, 100),

	smokeAnimation(Shared::smokeTexture, 350, 350, 11, 0.1f, 50, 50),
	throwWaterToLeftAnimation(Shared::playerReverseTexture, 210, 256, 6, 0.166f, 100, 100),
	throwWaterToRightAnimation(texture, 194, 256, 6, 0.166f, 100, 100)
{
	playerSprite.setPosition(sf::Vector2f(400, 0));
	playerSprite.setTexture(texture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

	swordSprite.setTexture(Shared::swordTexture);
	assets.resize(playerSprite, 100, 100);
	assets.resize(swordSprite, 30, 50);

	velocityY = 0;
	gravity = 1300.f;
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
	isRangedAttacking = false;
	setAnimationDamage = false;	
	canAttack = true;
	takingDamage = false;
	isDead = false;
	canDisplayGameOverBool = false;	
	isRepairing = false;
	progress = 0;
	isThrowingWater = false;

	energy = 100.f;
	maxEnergy = 100.f;
	jetpackPower = -3.f;
	energyConsumption = 10.f;
	energyRecharge = 0.1f;
	hpRecharge = 0.1f;
	surchauffe = 0.f;
	maxSurchauffe = 100.f;
	surchauffeRecharge = 0.05f;

	lifeBarSprite.setTexture(Shared::lifeBar2Texture);
	assets.resize(lifeBarSprite, 300, 100);

	energyBarSprite.setTexture(Shared::energyBarTexture);
	assets.resize(energyBarSprite, 268, 100);

	progressBarSprite.setTexture(Shared::progressBarTexture);
	assets.resize(progressBarSprite, 400, 50);

	surchauffeBarSprite.setTexture(Shared::surchauffeBarTexture);
	assets.resize(surchauffeBarSprite, 300, 90);

	damage = 15;
	hp = 100.f; // -------------------------------------------------------------------------------------------HP---------------
	maxHp = 100.f;

	daySprite.setTexture(Shared::dayTexture);
	assets.resize(daySprite, 150, 120);
	nightSprite.setTexture(Shared::nightTexture);
	assets.resize(nightSprite, 150, 120);
}

void Player::animate(float deltaTime) {

	// Gestion de la mort
	if (isDead) {
		(lastDepIsLeft ? deathToLeftAnimation : deathToRightAnimation).update(deltaTime);
		(lastDepIsLeft ? deathToLeftAnimation : deathToRightAnimation).applyToSprite(playerSprite, 9);
		return;
	}

	// Gestion des dégâts
	if (setAnimationDamage) {
		(lastDepIsLeft ? takeDamageToLeftAnimation : takeDamageToRightAnimation).update(deltaTime);
		(lastDepIsLeft ? takeDamageToLeftAnimation : takeDamageToRightAnimation).applyToSprite(playerSprite, 2);
		return;
	}

	// Gestion du mouvement et des actions
	if (std::abs(velocityY) < 100) { // Joueur au sol
		if (std::abs(velocityX) > 1) { // Déplacement
			(lastDepIsLeft ? walkToLeftAnimation : walkToRightAnimation).update(deltaTime);
			(lastDepIsLeft ? walkToLeftAnimation : walkToRightAnimation).applyToSprite(playerSprite, 0);
		}
		else { // Statique
			(lastDepIsLeft ? staticToLeftAnimation : staticToRightAnimation).update(deltaTime);
			(lastDepIsLeft ? staticToLeftAnimation : staticToRightAnimation).applyToSprite(playerSprite, 1);
		}
	}
	else { // En l'air (saut ou accroché)
		if (hangedToWallsLeft || hangedToWallsRight) {
			(hangedToWallsLeft ? hangedToRightAnimation : hangedToLefAnimation).update(deltaTime);
			(hangedToWallsLeft ? hangedToRightAnimation : hangedToLefAnimation).applyToSprite(playerSprite, 8);
		}
		else { // Saut normal
			(lastDepIsLeft ? jumpToLeftAnimation : jumpToRightAnimation).update(deltaTime);
			(lastDepIsLeft ? jumpToLeftAnimation : jumpToRightAnimation).applyToSprite(playerSprite, 8);
		}
	}

	// Gestion des attaques
	if (isAttacking) {
		(lastDepIsLeft ? attackToLeftAnimation : attackToRightAnimation).update(deltaTime);
		(lastDepIsLeft ? attackToLeftAnimation : attackToRightAnimation).applyToSprite(playerSprite, 5);
	}

	if (isRangedAttacking) {
		(lastDepIsLeft ? rangedAttackToLeftAnimation : rangedAttackToRightAnimation).update(deltaTime);
		(lastDepIsLeft ? rangedAttackToLeftAnimation : rangedAttackToRightAnimation).applyToSprite(playerSprite, 4);
	}

	if (isRepairing) {
		(lastDepIsLeft ? repairToLeftAnimation : repairToRightAnimation).update(deltaTime);
		(lastDepIsLeft ? repairToLeftAnimation : repairToRightAnimation).applyToSprite(playerSprite, 10);
	}
	if (isThrowingWater) {
		(lastDepIsLeft ? throwWaterToLeftAnimation : throwWaterToRightAnimation).update(deltaTime);
		(lastDepIsLeft ? throwWaterToLeftAnimation : throwWaterToRightAnimation).applyToSprite(playerSprite, 8);
	}

}

void Player::update(const std::vector<unique_ptr<Tiles>>& tiles, sf::RenderWindow& window, sf::View& view, float deltaTime, bool isDay, bool isInTheSun) {
	// méthode pour mettre à jour le joueur
	statsManager(isDay, isInTheSun);
	if (hp <= 0) {
		if (!isDead) {
			isDead = true;
			death.restart();
		}
		if (death.getElapsedTime().asSeconds() >= 1.8f) {
			canDisplayGameOverBool = true;
		}
	}

	animate(deltaTime);
	collide(tiles);
	if (!isDead) {
		jump(deltaTime);
		deplacement(deltaTime);
		attack(deltaTime);
	}
	updateHUD(view);
	updateProjectiles(deltaTime, window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) || sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 5)) {
		if (!isDead) { rangedAttack(); }
	}
	if (rangedAttackClockDuration.getElapsedTime().asSeconds() >= 1.0f) { isRangedAttacking = false; }
	else { isRangedAttacking = true; }

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) || sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 4)) {
		if (!isDead) { throwWater(); }
	}
	if (throwWaterClockDuration.getElapsedTime().asSeconds() >= 1.0f) { isThrowingWater = false; }
	else { isThrowingWater = true; }

}



void Player::fix(const std::vector<std::unique_ptr<Reparable>>& re) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		for (auto& it : re) {
			if(playerSprite.getGlobalBounds().intersects(it->getSprite().getGlobalBounds()) && it->fixed == false)
			{
				it->fixing();
			}
		}
	}
}
bool Player::getCanDisplayGameOverBool() const { return canDisplayGameOverBool; }

void Player::statsManager(bool isDay, bool isInTheSun) {
	if (energy < maxEnergy) { energy += energyRecharge; }
	if (energy <= 0) { energy = 0; }

	if (isDay) {
		if (hp < maxHp) { hp += hpRecharge; }
		if (hp <= 0) { hp = 0; }
		if (isInTheSun) {
			if (surchauffe < maxSurchauffe) { surchauffe += surchauffeRecharge; }
		}
		else {
			if (surchauffe > 0) { surchauffe -= surchauffeRecharge * 4; }
		}
	}
	else {
		if (surchauffe > 0) { surchauffe -= surchauffeRecharge; }
	}
	if (surchauffe >= maxSurchauffe) { hp = -999; }
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

			float playerTopCenterX = playerBounds.left + playerBounds.width / 2;
			float playerTopCenterY = playerBounds.top;

			if (velocityY < 0 && playerTopCenterY < platformBottom && playerTopCenterY > platformTop &&
				playerTopCenterX > platformLeft && playerTopCenterX < platformRight) { // haut
				if (!hangedToWallsRight && !hangedToWallsLeft) {
					velocityY = 0;
					playerSprite.setPosition(playerSprite.getPosition().x, platformBottom);
				}
			}

			else if (velocityY >= 0 && playerBottom > platformTop && playerTop < platformTop + groundTolerance) { // bas
				isOnGround = true;
				velocityY = 0;
				playerSprite.setPosition(playerSprite.getPosition().x, platformTop - playerSprite.getGlobalBounds().height);
			}
			else if (playerRight > platformLeft && playerLeft < platformLeft + offsetTolerance) { // gauche
				playerSprite.setPosition(platformLeft - playerBounds.width, playerSprite.getPosition().y);
				if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 0)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					hangedToWallsLeft = true;
				}
			}
			else if (playerLeft < platformRight && playerRight > platformRight - offsetTolerance) { // droite
				playerSprite.setPosition(platformRight, playerSprite.getPosition().y);
				if ((sf::Joystick::isConnected(0) && sf::Joystick::isButtonPressed(0, 0)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					hangedToWallsRight = true;
				}
			}
		}
	}
}

void Player::deplacement(float deltaTime) {
	// méthode pour gérer le déplacement du joueur
	deltaTime = std::min(deltaTime, 0.1f);
	const float acceleration = 1000.0f;
	const float friction = 2000.0f;
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
				shortRangeDamage = 0.1f;
				energy -= 5.0;
				attackClock.restart();
				attackDurationClock.restart();
			}
		}
		else {
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && energy > 5.0) {
				shortRangeDamage = 0.1f;
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

	float spacing = 20;
	float sizeY = 36;

	float hudX = viewCenter.x - (viewSize.x / 2) + spacing;
	float hudY = viewCenter.y - (viewSize.y / 2) + spacing;

	shapeFillHP.setSize(sf::Vector2f(((hp / maxHp) * 100) * 2.67f, sizeY));
	shapeFillHP.setFillColor(sf::Color::Red);

	shapeFillEnergy.setSize(sf::Vector2f(((energy / maxEnergy) * 100) * 2.62f, sizeY));
	shapeFillEnergy.setFillColor(sf::Color::Green);

	shapeFillSurchauffe.setSize(sf::Vector2f(((surchauffe / maxSurchauffe) * 100) * 2.62f, sizeY));
	shapeFillSurchauffe.setFillColor(sf::Color::White);

	lifeBarSprite.setPosition(hudX, hudY);
	energyBarSprite.setPosition(hudX + 15, hudY + lifeBarSprite.getGlobalBounds().height + spacing);
	surchauffeBarSprite.setPosition(hudX, hudY + lifeBarSprite.getGlobalBounds().height * 2 + (spacing * 2));
	progressBarSprite.setPosition(hudX + Config::WINDOW_WIDTH / 2 - progressBarSprite.getGlobalBounds().width / 2, hudY + spacing);

	shapeFillEnergy.setPosition(hudX + spacing - 1, hudY + lifeBarSprite.getGlobalBounds().height + 53);
	shapeFillHP.setPosition(hudX + spacing - 2, hudY + (spacing * 2) + 8);
	shapeFillSurchauffe.setPosition(hudX + spacing, hudY + lifeBarSprite.getGlobalBounds().height * 2 + (spacing * 3.6));
	//------ENERGY------
	//------DAY/NIGHT------
	daySprite.setPosition(viewCenter.x + viewSize.x / 2 - daySprite.getGlobalBounds().width - spacing, viewCenter.y - viewSize.y / 2 + spacing);
	nightSprite.setPosition(viewCenter.x + viewSize.x / 2 - daySprite.getGlobalBounds().width - spacing, viewCenter.y - viewSize.y / 2 + spacing);
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
		AudioManager::getInstance().setSoundVolume("tir", 10);
		AudioManager::getInstance().playSound("tir");
		rangedAttackClock.restart();
		rangedAttackClockDuration.restart();
	}
}

void Player::throwWater() {
	if (throwWaterClock.getElapsedTime().asSeconds() >= 0.5f) {
		sf::Vector2f spawnPos = playerSprite.getPosition();
		spawnPos.x += lastDepIsLeft ? -20 : playerSprite.getGlobalBounds().width;
		Projectile newProjectile(Shared::waterProjTexture, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
		newProjectile.resize(30, 30);
		projectilesWater.push_back(newProjectile);
		energy -= 10.0f;
		throwWaterClock.restart();
		throwWaterClockDuration.restart();
	}
}

void Player::updateProjectiles(float deltaTime, sf::RenderWindow& window) {
	// méthode pour mettre à jour les projectiles du joueur
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->update(deltaTime);
		++it;
	}
	for (auto it = projectilesWater.begin(); it != projectilesWater.end();) {
		it->updateForWater(deltaTime);
		++it;
	}
}

bool Player::takeDamage(sf::Sprite projEnnemi, float deltaTime) {
	// méthode pour gérer les dégâts infligés au joueur
	if (playerSprite.getGlobalBounds().intersects(projEnnemi.getGlobalBounds())) {
		takeDamageClock.restart();

		AudioManager::getInstance().playSound("hit1");
		hp -= 5;
		takingDamage = true;
		setAnimationDamage = true;
	}

	if (takeDamageClock.getElapsedTime().asSeconds() > 0.5) {
		setAnimationDamage = false;
	}
	return takingDamage;
}

bool Player::takeDamageSimple(float deltaTime) {
	// méthode pour gérer les dégâts infligés au joueur (simple)
	takeDamageClock.restart();

	AudioManager::getInstance().playSound("hit1");
	hp -= 0.1;
	takingDamage = true;
	setAnimationDamage = true;
	

	if (takeDamageClock.getElapsedTime().asSeconds() > 0.5) {
		setAnimationDamage = false;
	}
	return takingDamage;
}

void Player::augmenterEnergie(int quantite) {
	energy += quantite;
	if (energy > maxEnergy) {
		energy = maxEnergy;
	}
}

void Player::augmenterHP(int quantite) {
	hp += quantite;
	if (hp > 100) {
		hp = 100;
	}
}

//getters/setters
float Player::getHP() const { return hp; }
float Player::getEnergie() const { return energy; }
sf::Sprite Player::getShape() const { return playerSprite; }
sf::Sprite Player::getShapeAtk() const { return swordSprite; }
sf::Sprite Player::getShapeSmoke() const { return smokeSprite; }
sf::Sprite Player::getLifeBarSprite() const { return lifeBarSprite; }
sf::Sprite Player::getLifeBar2Sprite() const { return lifeBarSprite; }
sf::Sprite Player::getEnergyBarSprite() const { return energyBarSprite; }
sf::Sprite Player::getProgressBarSprite() const { return progressBarSprite; }
sf::Sprite Player::getSurchauffeBarSprite() const { return surchauffeBarSprite; }
sf::RectangleShape Player::getShapeFillEnergy() const { return shapeFillEnergy; }
sf::RectangleShape Player::getShapeFillHP() const { return shapeFillHP; }
sf::RectangleShape Player::getShapeSurchauffe() const { return shapeFillSurchauffe; }
std::vector<Projectile> Player::getProj() const { return projectiles; }
std::vector<Projectile> Player::getProjWater() const { return projectilesWater; }
sf::Sprite Player::getProjShape(Projectile& proj) const { return proj.getSprite(); }
sf::Sprite Player::getProjWaterShape(Projectile& proj) const { return proj.getSprite(); }
sf::Sprite Player::getDaySprite() const { return daySprite; }
sf::Sprite Player::getNightSprite() const { return nightSprite; }
bool Player::getTakingDamageBool() const { return takingDamage; }
void Player::setTakingDamageBool(bool takingDamage) { this->takingDamage = takingDamage; }

Player::~Player() {
	projectiles.clear();
}

void Player::resetPlayer() {
	playerSprite.setPosition(sf::Vector2f(400, 0));
	playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));

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
	isRangedAttacking = false;
	setAnimationDamage = false;
	canAttack = true;
	takingDamage = false;
	isDead = false;
	canDisplayGameOverBool = false;
	isRepairing = false;
	progress = 0;
	isThrowingWater = false;

	energy = 100.f;
	maxEnergy = 100.f;
	jetpackPower = -3.f;
	energyConsumption = 10.f;
	energyRecharge = 0.1f;
	hpRecharge = 0.1f;
	surchauffe = 0.f;
	maxSurchauffe = 100.f;
	surchauffeRecharge = 0.05f;

	damage = 15;
	hp = 100.f;
	maxHp = 100.f;
}