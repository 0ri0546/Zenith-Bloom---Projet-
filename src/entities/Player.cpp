#include "Player.hpp"

Player::Player() {
	Assets assets;
	Shared::playerSprite.setTexture(Shared::playerTexture);
	Shared::smokeSprite.setTexture(Shared::smokeTexture);
	Shared::swordSprite.setTexture(Shared::swordTexture);
	assets.resize(Shared::playerSprite, 50, 50);
	assets.resize(Shared::smokeSprite, 30, 50);
	assets.resize(Shared::swordSprite, 30, 50);

	velocityY = 0;
	gravity = 0.5f;
	isOnGround = false;

	jumpCount = maxJumps;
	canJump = true;

	lastDepIsLeft = true;

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

void Player::update(const std::vector<Platform>& platforms, sf::RenderWindow& window, sf::View& view) {
	//reste à faire :
	//la fonction Player::boost() "le cyborg peut utiliser ses réacteurs pour se propulser en avant, ce qui consommera 15 points d'energie"
	//afficher les HUD (vie (coeurs ?), progression dans le niveau, etc...)

	border();
	collide(platforms);
	jump();
	//useJetpack();
	deplacement();
	attack();
	//rangedAttack(window);
	//std::cout << "Nombre de projectiles : " << projectiles.size() << std::endl;

	updateHUDEnergy(view);
	std::cout << "energie : " << energy << std::endl;
}

void Player::jump() {
	//reste à faire :
	//ajouter le systeme de saut plus haut quand on maintient la touche space enfoncée

	if (!isOnGround) {
		velocityY += gravity;
	}
	else {
		jumpCount = maxJumps;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpCount > 0 && canJump) {
		velocityY = -10.0f;
		jumpCount--;
		canJump = false;
		if (jumpCount == 0) {
			energy -= energyConsumption;
		}
	}

	if (jumpCount == 0) { //pour la fumée
		if (lastDepIsLeft) {
			Shared::smokeSprite.setPosition(Shared::playerSprite.getPosition().x + Shared::playerSprite.getGlobalBounds().width / 2, Shared::playerSprite.getPosition().y + 30);
		}
		else {
			Shared::smokeSprite.setPosition(Shared::playerSprite.getPosition().x - 30 + Shared::playerSprite.getGlobalBounds().width / 2, Shared::playerSprite.getPosition().y + 30);
		}
	}
	else {
		Shared::smokeSprite.setPosition(9999, 9999);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		canJump = true;
		if (energy < maxJetpackEnergy) {
			energy += energyRecharge;
		}
	}

	Shared::playerSprite.move(0, velocityY);
}

void Player::collide(const std::vector<Platform>& platforms) { //collision joueur/platforms
	isOnGround = false;

	for (const auto& platform : platforms) {
		if (Shared::playerSprite.getGlobalBounds().intersects(platform.getShape().getGlobalBounds())) {
			sf::FloatRect playerBounds = Shared::playerSprite.getGlobalBounds();
			sf::FloatRect platformBounds = platform.getShape().getGlobalBounds();

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
				Shared::playerSprite.setPosition(Shared::playerSprite.getPosition().x, platformTop - Shared::playerSprite.getGlobalBounds().height);
			}
			else if (velocityY < 0 && playerTop < platformBottom && playerBottom > platformBottom) { //haut
				velocityY = 0;
				Shared::playerSprite.setPosition(Shared::playerSprite.getPosition().x, platformBottom);
			}
			else if (playerRight > platformLeft && playerLeft < platformLeft && velocityY >= 0) { //gauche
				Shared::playerSprite.setPosition(platformLeft - playerBounds.width, Shared::playerSprite.getPosition().y);
			}
			else if (playerLeft < platformRight && playerRight > platformRight && velocityY >= 0) { //droite
				Shared::playerSprite.setPosition(platformRight, Shared::playerSprite.getPosition().y);
			}
		}
	}
	Shared::playerSprite.getGlobalBounds().width;
}

void Player::deplacement() {
	//reste à faire :
	//le joueur doit "glisser" si j'ai bien compris
	sf::Vector2f nPos;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		nPos.x = 10.0f;
		lastDepIsLeft = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		nPos.x = -10.0f;
		lastDepIsLeft = true;
	}
	Shared::playerSprite.move(nPos);
}

void Player::border() {
	//reste à faire :
	//ajuster selon nos besoins
	if (Shared::playerSprite.getPosition().x <= 0) {
		Shared::playerSprite.setPosition(0, Shared::playerSprite.getPosition().y);
	}
	if (Shared::playerSprite.getPosition().x + Shared::playerSprite.getGlobalBounds().width >= WIDTH) {
		Shared::playerSprite.setPosition(WIDTH - Shared::playerSprite.getGlobalBounds().width, Shared::playerSprite.getPosition().y);
	}
}

float Player::attack() {
	float shortRangeDamage = 0.f;
	if (lastDepIsLeft) {
		Shared::swordSprite.setPosition(Shared::playerSprite.getPosition().x - 30, Shared::playerSprite.getPosition().y);
	}
	else {
		Shared::swordSprite.setPosition(Shared::playerSprite.getPosition().x + Shared::playerSprite.getGlobalBounds().width, Shared::playerSprite.getPosition().y);
	}

	if (attackClock.getElapsedTime().asSeconds() >= 0.5f) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && energy > 5.0) {
			shortRangeDamage = damage;
			
			energy -= 5.0;
			attackClock.restart();
			attackDurationClock.restart();
		}
	}

	if (attackDurationClock.getElapsedTime().asSeconds() >= 1.0f) { //valeur modifiable selon l'animation de l'attaque
		Shared::swordSprite.setPosition(9999, 9999);
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
	return Shared::playerSprite;
}

sf::Sprite Player::getShapeAtk() const {
	return Shared::swordSprite;
}

sf::Sprite Player::getShapeSmoke() const {
	return Shared::smokeSprite;
}

sf::RectangleShape Player::getShapeHUDEnergy() const {
	return shapeEnergy;
}

sf::RectangleShape Player::getShapeFillEnergy() const {
	return shapeFillEnergy;
}