#include "FSM.hpp"

Ennemy::Ennemy(unsigned long long x, unsigned long long y) : x(x), y(y) {
	spriteEnnemy.setTexture(Shared::ennemyTexture);
	assets.resize(spriteEnnemy, 100, 100);
	spriteEnnemy.setOrigin(spriteEnnemy.getLocalBounds().width / 2, spriteEnnemy.getLocalBounds().height / 2);
	spriteEnnemy.setPosition(x, y);
	currentState = CHASE;
	lastDepIsLeft = false;
	speed = 0;
	pathIndex = 0;
}

sf::Sprite Ennemy::getSprite() const {
	return spriteEnnemy;
}

void Ennemy::patrol(Player& player) {
	/*{
		currentWaypoint = (currentWaypoint + 1) % 2;
	}
	if (player.getShape().getPosition().x - spriteEnnemy.getPosition().x < radiusDetection || player.getShape().getPosition().y - spriteEnnemy.getPosition().y < radiusDetection) {
		currentState = CHASE;
	}
	else {
		currentState = PATROL;
	}
	if (abs(player.getShape().getPosition().x - spriteEnnemy.getPosition().x < radiusDetection) && abs(player.getShape().getPosition().y - spriteEnnemy.getPosition().y < radiusDetection)) {
		currentState = CHASE;
	}
	else {
		currentState = PATROL;
	}*/
	for (auto& detectionCircles : detectionCircles) {
		if (player.getShape().getGlobalBounds().intersects(detectionCircles.getGlobalBounds())) {
			currentState = CHASE;
		}
		else {
			currentState = PATROL;
		}
	}
}

void Ennemy::chase(Player& player) {
	speed = 1;
	sf::Vector2f direction(
		speed * copysign(1.0f, player.getShape().getPosition().x - spriteEnnemy.getPosition().x),
		speed * copysign(1.0f, player.getShape().getPosition().y - spriteEnnemy.getPosition().y));

	moveForCol = direction;
	spriteEnnemy.move(direction);

	if (direction.x < 0) {
		lastDepIsLeft = true;
	}
	else if (direction.x > 0) {
		lastDepIsLeft = false;
	}
}

void Ennemy::collision(Player& player, vector<Projectile>& projectile, vector<Ennemy>& ennemies) {
	for (auto proj : projectile) {
		if (player.getProjShape(proj).getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
			currentState = DEAD;
			
			for (int i = 0; i < projectile.size(); i++) {
				if (proj.getSprite().getPosition() == projectile[i].getSprite().getPosition()) {
					projectile.erase(projectile.begin() + i);
				}
			}
		}
	}
	
	if (player.getShape().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) { //quand les ennemis sont sur le joueur, pour ne pas qu'ils tremblent
		sf::Vector2f direction = spriteEnnemy.getPosition() - player.getShape().getPosition();
		float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
		float minDistance = 50.0f;
		float pushForce = 1.f;

		if (distance < minDistance && distance > 5.0f) {
			direction /= distance;
			spriteEnnemy.move(direction * pushForce);
		}
	}

	if (player.getShapeAtk().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
		currentState = DEAD;
	}

	for (int i = 0; i < ennemies.size(); i++) {
		if (ennemies[i].currentState == DEAD){
			ennemies.erase(ennemies.begin()+i);
		}
	}
}

void Ennemy::colEnnemyToEnnemy(vector<Ennemy>& ennemies) {
	for (size_t i = 0; i < ennemies.size(); i++) {
		for (size_t j = i + 1; j < ennemies.size(); j++) {
			if (ennemies[i].getSprite().getGlobalBounds().intersects(ennemies[j].getSprite().getGlobalBounds())) {
				sf::Vector2f direction = ennemies[i].getSprite().getPosition() - ennemies[j].getSprite().getPosition();
				float length = sqrt(direction.x * direction.x + direction.y * direction.y);
				if (length != 0) {
					direction /= length;
					float reboundForce = 0.5f; 
					ennemies[i].spriteEnnemy.move(direction * reboundForce);
					ennemies[j].spriteEnnemy.move(-direction * reboundForce);
				}
			}
		}
	}
}

void Ennemy::runEnnemy(Player& player, sf::RenderWindow& window, vector<Projectile>& projectile, vector<Ennemy>& ennemies, float deltaTime) {
	colEnnemyToEnnemy(ennemies);
	switch (currentState) {
	case PATROL:
		patrol(player);
		break;
	case SEARCH:
		break;
	case CHASE:
		chase(player);
		break;
	case DEAD:
		break;
	}
	
	//detectionCircle.setRadius(radiusDetection);
	for (auto& detectionCircles : detectionCircles) {
		detectionCircles.setRadius(radiusDetection);
		detectionCircles.setOrigin(radiusDetection, radiusDetection);
		detectionCircles.setFillColor(sf::Color::Black);

		/*for (auto& spritEnnemies : spritEnnemies) {
			detectionCircles.setPosition(spritEnnemies.getPosition());
			detectionCircles.setOrigin(spritEnnemies.getOrigin());
		}*/
	}
	collision(player, projectile, ennemies);
	colEnnemyToEnnemy(ennemies);
	updateProjectiles(deltaTime, window);
	//detectionCircle.setPosition(spriteEnnemy.getPosition());
	rangedAttack();
}

void Ennemy::rangedAttack() {
	if (rangedAttackClock.getElapsedTime().asSeconds() >= 0.3f) {
		sf::Vector2f spawnPos = spriteEnnemy.getPosition();
		spawnPos.x += lastDepIsLeft ? -20 : spriteEnnemy.getGlobalBounds().width;

		Projectile newProjectile(Shared::projectileTexture, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
		newProjectile.resize(20, 20);
		projectiles.push_back(newProjectile);
		rangedAttackClock.restart();
	}
}

void Ennemy::updateProjectiles(float deltaTime, sf::RenderWindow& window) {
	for (auto it = projectiles.begin(); it != projectiles.end();) {
		it->update(deltaTime);
		++it;
	}
}


void Ennemy::draw(sf::RenderWindow& window) {
	for (auto& detectionCircles : detectionCircles) {
		window.draw(detectionCircles);
	}
	for (auto& spritEnnemies : spritEnnemies){
		window.draw(spritEnnemies);
	}
}

std::vector<Projectile> Ennemy::getProj() const { return projectiles; }
sf::Sprite Ennemy::getProjShape(Projectile& proj) const { return proj.getSprite(); }
