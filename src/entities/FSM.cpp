#include "../entities/FSM.hpp"

Ennemy::Ennemy(unsigned long long x, unsigned long long y) : x(x), y(y) {
    spriteEnnemy.setTexture(Shared::ennemyTexture);
    assets.resize(spriteEnnemy, 100, 100);
    spriteEnnemy.setOrigin(spriteEnnemy.getLocalBounds().width / 2, spriteEnnemy.getLocalBounds().height / 2);
    spriteEnnemy.setPosition(x, y);
    currentState = CHASE;
    lastDepIsLeft = false;
    speed = 0;
    pathIndex = 0;
    gravity = 0.5;
    velocityY = 0;
}

sf::Sprite Ennemy::getSprite() const {
    return spriteEnnemy;
}

void Ennemy::patrol(Player& player) {
    for (auto& detectionCircle : detectionCircles) {
        if (player.getShape().getGlobalBounds().intersects(detectionCircle.getGlobalBounds())) {
            currentState = CHASE;
            return;
        }
    }
    currentState = PATROL;
}

void Ennemy::chase(Player& player) {
    speed = 1;
    sf::Vector2f direction(
        speed * copysign(4.0f, player.getShape().getPosition().x - spriteEnnemy.getPosition().x),
        speed * copysign(0.0f, velocityY + spriteEnnemy.getPosition().y)
    );

    moveForCol = direction;
    if (onTheGround)
        spriteEnnemy.move(direction.x, 0);
    else
        spriteEnnemy.move(direction);

    lastDepIsLeft = direction.x < 0;
}

void Ennemy::collision(Player& player, std::vector<Projectile>& projectile, std::vector<Ennemy>& ennemies) {
    for (auto it = projectile.begin(); it != projectile.end();) {
        if (player.getProjShape(*it).getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
            currentState = DEAD;
            it = projectile.erase(it);
        }
        else {
            ++it;
        }
    }

    if (player.getShape().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
        sf::Vector2f direction = spriteEnnemy.getPosition() - player.getShape().getPosition();
        float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
        float minDistance = 50.0f;
        float pushForce = 1.f;

        if (distance < minDistance && distance > 5.0f) {
            direction /= distance;
            if (onTheGround)
                spriteEnnemy.move(direction.x * pushForce, 0);
            else
                spriteEnnemy.move(direction * pushForce);
        }
    }

    if (player.getShapeAtk().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
        currentState = DEAD;
    }

    ennemies.erase(std::remove_if(ennemies.begin(), ennemies.end(), [](const Ennemy& e) { return e.currentState == DEAD; }), ennemies.end());
}

void Ennemy::colEnnemyToEnnemy(std::vector<Ennemy>& ennemies) {
    for (size_t i = 0; i < ennemies.size(); ++i) {
        for (size_t j = i + 1; j < ennemies.size(); ++j) {
            if (ennemies[i].getSprite().getGlobalBounds().intersects(ennemies[j].getSprite().getGlobalBounds())) {
                sf::Vector2f direction = ennemies[i].getSprite().getPosition() - ennemies[j].getSprite().getPosition();
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                if (length != 0) {
                    direction /= length;
                    float reboundForce = 0.5f;
                    ennemies[i].spriteEnnemy.move(direction.x * reboundForce, direction.y * reboundForce);
                    ennemies[j].spriteEnnemy.move(-direction.x * reboundForce, -direction.y * reboundForce);
                }
            }
        }
    }
}

void Ennemy::colEnnemyToPlayer(Player& player, std::vector<Ennemy>& ennemies) {
    if (spriteEnnemy.getGlobalBounds().intersects(player.getShape().getGlobalBounds())) {
        sf::Vector2f direction = spriteEnnemy.getPosition() - player.getShape().getPosition();
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        float minDistance = 50.0f;

        if (length < minDistance) {
            direction /= length;
            float overlap = minDistance - length;
            sf::Vector2f correction = direction * overlap;

            if (onTheGround)
                spriteEnnemy.move(correction.x, 0);
            else
                spriteEnnemy.move(correction);
        }
    }
}

void Ennemy::colEnnemiToGround(std::vector<Ennemy>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles) {
    onTheGround = std::any_of(tiles.begin(), tiles.end(), [this](const std::unique_ptr<Tiles>& tile) {
        return spriteEnnemy.getGlobalBounds().intersects(tile->getSprite().getGlobalBounds());
        });
}

void Ennemy::runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, std::vector<Ennemy>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) {
    colEnnemiToGround(ennemies, tiles);

    if (!onTheGround) {
        velocityY += gravity;
        spriteEnnemy.move(0, velocityY);
    }
    else {
        velocityY = 0;
    }

    colEnnemyToEnnemy(ennemies);
    colEnnemyToPlayer(player, ennemies);

    if (onTheGround) {
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
    }

    for (auto& detectionCircle : detectionCircles) {
        detectionCircle.setRadius(radiusDetection);
        detectionCircle.setOrigin(radiusDetection, radiusDetection);
        detectionCircle.setFillColor(sf::Color::Black);
        detectionCircle.setPosition(spriteEnnemy.getPosition());
    }

    collision(player, projectile, ennemies);
    updateProjectiles(deltaTime, window);
    rangedAttack();

	//fillEmptySpacesWithShadows(tiles); // Ombres
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

void Ennemy::fillEmptySpacesWithShadows(std::vector<std::unique_ptr<Tiles>>& tiles) {
    for (auto& tile : tiles) {
        if (!tile->hasShadow() && tile->isEmpty()) {
            sf::FloatRect tileBounds = tile->getSprite().getGlobalBounds();
            for (auto& otherTile : tiles) {
                if (otherTile.get() != tile.get()) {
                    sf::FloatRect otherTileBounds = otherTile->getSprite().getGlobalBounds();
                    if (tileBounds.left == otherTileBounds.left && tileBounds.top == otherTileBounds.top + otherTileBounds.height) {
                        if (otherTile->hasShadow() || otherTile->getValue() < 10) {
                            tile->setShadow(true);
                            break;
                        }
                    }
                }
            }
        }
    }
}

std::vector<Projectile>& Ennemy::getProj() { return projectiles; }
sf::Sprite Ennemy::getProjShape(Projectile& proj) const { return proj.getSprite(); }

Ennemy::~Ennemy() {}
