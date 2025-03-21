#include "../entities/drone.hpp"

Drone::Drone(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY)
    : Ennemy(x, y, text, textR, xT, yT, scaleX, scaleY, textRecX, textRecY), 
    deplacementAnimation(Shared::droneTexture, 719.81, 404.12, 3, 0.4f, scaleX, scaleY)
        {
    life = 30;
    spriteEnnemy.setTexture(Shared::droneTexture);
    initialPosition = spriteEnnemy.getPosition();
    attackClock.restart();
    directionTimer = 0.0f;
}

void Drone::attack(Player& player, float deltaTime) {
    if (attackClock.getElapsedTime().asSeconds() >= 0.5f) {

        sf::Vector2f spawnPos = spriteEnnemy.getPosition();
        spawnPos.x += 110;
        spawnPos.y += 170;
        Projectile newProjectile(Shared::waterProjTexture, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
        newProjectile.resize(30, 30);

        projectiles.push_back(newProjectile);
        attackClock.restart();
        attackClockDuration.restart();
    }
}

void Drone::updateProjectiles(float deltaTime, sf::RenderWindow& window) {
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        it->updateForDrone(deltaTime);
        ++it;
    }
}

sf::Sprite Drone::getProjShape(Projectile& proj) const { return proj.getSprite(); }
std::vector<Projectile>& Drone::getProj() { return projectilesDrone; }

void Drone::runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectiles, std::vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) {
    colEnnemiToGround(ennemies, tiles);

    directionTimer += deltaTime;
    if (directionTimer >= 2.0f) {  
        directionTimer = 0.0f;
        currentDirection = static_cast<Direction>((currentDirection + 1) % 4); 
    }

    float movementSpeed = 300.0f;

    float newPosX = spriteEnnemy.getPosition().x;
    float newPosY = spriteEnnemy.getPosition().y;

    switch (currentDirection) {
    case LEFT:
        newPosX -= movementSpeed * deltaTime; 
        break;
    case RIGHT:
        newPosX += movementSpeed * deltaTime; 
        break;
    case UP:
        newPosY -= movementSpeed * deltaTime;
        break;
    case DOWN:
        newPosY += movementSpeed * deltaTime;  
        break;
    }

    float limit = 400.0f;

    if (newPosX < initialPosition.x - limit) {
        newPosX = initialPosition.x - limit;  
    }
    else if (newPosX > initialPosition.x + limit) {
        newPosX = initialPosition.x + limit; 
    }

    if (newPosY < initialPosition.y - limit) {
        newPosY = initialPosition.y - limit; 
    }
    else if (newPosY > initialPosition.y + limit) {
        newPosY = initialPosition.y + limit;
    }

    spriteEnnemy.setPosition(newPosX, newPosY);

    attack(player, deltaTime);

    for (const auto& proj : projectilesDrone) {
        window.draw(proj.getSprite());
    }
    deplacementAnimation.update(deltaTime);
    deplacementAnimation.applyToSprite(spriteEnnemy, 0);
 
    collision(player, projectiles, ennemies, deltaTime);

    updateProjectiles(deltaTime, window);
}


