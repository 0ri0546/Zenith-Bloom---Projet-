#include "../entities/FSM.hpp"

Ennemy::Ennemy(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY) : x(x), y(y), 

    attackAnim(text, xT, yT, 4, 0.15f, scaleX, scaleY),
    walkAnim(text, xT, yT, 4, 0.05f, scaleX, scaleY),
    standAnim(text, xT, yT, 1, 0.5f, scaleX, scaleY),
    hitAnim(text, xT, yT, 1, 3.f, scaleX, scaleY),

    walkAnimR(textR, xT, yT, 4, 0.05f, scaleX, scaleY),
    hitAnimR(textR, xT, yT, 1, 3.f, scaleX, scaleY),
    attackAnimR(textR, xT, yT, 4, 0.15f, scaleX, scaleY)
{


    spriteEnnemy.setTexture(text);
    spriteEnnemy.setTextureRect(sf::IntRect(0,0,textRecX, textRecY)); //50, 30
    //assets.resize(spriteEnnemy, 100, 100);
    //spriteEnnemy.setScale(3, 3);
    spriteEnnemy.setOrigin(spriteEnnemy.getLocalBounds().width / 2, spriteEnnemy.getLocalBounds().height /2 );
    spriteEnnemy.setPosition(x, y);
    radiusDetection = 200.f;
    circle.setRadius(radiusDetection);
    circle.setOrigin(radiusDetection, radiusDetection);
    circle.setPosition(x, y);
    circle.setFillColor(sf::Color::Black);
    currentState = PATROL;
    
    lastDepIsLeft = false;
    speed = 1;
    pathIndex = 0;
    gravity = 1200;
    velocityY = 0;
    boxCol1 = 170;  
    boxCol2 = 40;
}

sf::Sprite Ennemy::getSprite() const {
    return spriteEnnemy;
}

void Ennemy::patrol(Player& player) {
    
    if (player.getShape().getGlobalBounds().intersects(circle.getGlobalBounds())) {
        currentState = CHASE;
        return;
    }
    
    //currentState = PATROL;
}

void Ennemy::chase(Player& player) {
    //speed = 1;
    inWalk = true;
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

void Ennemy::collision(Player& player, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, float deltaTime) {
    //takeDamageClock.getElapsedTime().asSeconds();
    for (auto it = projectile.begin(); it != projectile.end();) {
        if (player.getProjShape(*it).getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
            takeDamageClock.restart();
           
            life -= 1;
            /*hitAnim.update(deltaTime);
            hitAnim.takeSecondImage(spriteEnnemy, 2);*/
            if (life == 0) {
                AudioManager::getInstance().playSound("explo");
                currentState = DEAD;
            }
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
        AudioManager::getInstance().playSound("hit1");
        life -= 0.0001f;  
       
        takeDamageClock.restart();
        /*hitAnim.update(deltaTime);
        hitAnim.takeSecondImage(spriteEnnemy, 2);*/
        if (life == 0) {
            AudioManager::getInstance().playSound("explo");
            currentState = DEAD;
        }
    }

    if (takeDamageClock.getElapsedTime().asSeconds() <= 0.5f) {
        if (player.getShape().getPosition().x < spriteEnnemy.getPosition().x) {
            hitAnimR.update(deltaTime);
            hitAnimR.applyToSprite(spriteEnnemy, 1);
        }
        else
        {
            hitAnim.update(deltaTime);
            hitAnim.applyToSprite(spriteEnnemy, 1);
        }
    }
}

void Ennemy::colEnnemyToEnnemy(vector<std::unique_ptr<Ennemy>>& ennemies) {
    for (size_t i = 0; i < ennemies.size(); ++i) {
        for (size_t j = i + 1; j < ennemies.size(); ++j) {
            if (ennemies[i]->getSprite().getGlobalBounds().intersects(ennemies[j]->getSprite().getGlobalBounds())) {
                sf::Vector2f direction = ennemies[i]->getSprite().getPosition() - ennemies[j]->getSprite().getPosition();
                float length = sqrt(direction.x * direction.x + direction.y * direction.y);
                if (length != 0) {
                    direction /= length;
                    float reboundForce = 0.3f;

                    bool iOnGround = ennemies[i]->onTheGround;
                    bool jOnGround = ennemies[j]->onTheGround;
                    
                    if (!onTheGround ) {
                        ennemies[i]->spriteEnnemy.move(direction.x * reboundForce, direction.y * reboundForce);
                    }
                    if(!jOnGround)
                        ennemies[j]->spriteEnnemy.move(-direction.x * reboundForce, -direction.y * reboundForce);
                    else {
                        ennemies[i]->spriteEnnemy.move(direction.x * reboundForce, 0);
                        ennemies[j]->spriteEnnemy.move(-direction.x * reboundForce, 0);
                    }
                }
            }
        }
    }
}

void Ennemy::colEnnemyToPlayer(Player& player, vector<std::unique_ptr<Ennemy>>& ennemies) {
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

void Ennemy::colEnnemiToGround(vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles) {
    onTheGround = false;
    for (const auto& tile : tiles) {
        if (tile->getSprite().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds()) && tile->getSprite().getPosition().y > spriteEnnemy.getPosition().y) {
            spriteEnnemy.setPosition(spriteEnnemy.getPosition().x, tile->getSprite().getPosition().y - boxCol2);
            velocityY = 0;
            onTheGround = true;
        }
    }

   
}

void Ennemy::runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) {
    colEnnemiToGround(ennemies, tiles);

    if (!onTheGround) {
        velocityY += gravity * deltaTime;
        if (velocityY > maxFallSpeed) {
            velocityY = maxFallSpeed;
        }
        spriteEnnemy.move(0, velocityY * deltaTime);
    }
    else {
        velocityY = 0;
    }
    colEnnemyToEnnemy(ennemies);
    colEnnemyToPlayer(player, ennemies);
    circle.setPosition(spriteEnnemy.getPosition());
    if (onTheGround) {
        switch (currentState) {
        case PATROL: 
            standAnim.update(deltaTime);
            standAnim.applyToSprite(spriteEnnemy, 0);
            patrol(player);
            break;
        case SEARCH:
            break;
        case CHASE:
            if (player.getShape().getPosition().x < spriteEnnemy.getPosition().x) {
                lastDepIsLeft = true;
                walkAnimR.update(deltaTime);  
                walkAnimR.applyToSprite(spriteEnnemy, 0);
            }
            else {
                lastDepIsLeft = false;
                walkAnim.update(deltaTime);   
                walkAnim.applyToSprite(spriteEnnemy, 0);
            }

            chase(player);
            rangedAttack(deltaTime);
            break;
        case DEAD:

            break;
        case NIGHT:
            break;
        }
    }
    collision(player, projectile, ennemies, deltaTime);
    updateProjectiles(deltaTime, window);
}

void Ennemy::rangedAttack(float deltaTime) {
    if (rangedAttackClock.getElapsedTime().asSeconds() >= 1.f) {
        sf::Vector2f spawnPos = spriteEnnemy.getPosition();
        if (lastDepIsLeft == false) {
             
            spawnPos.x += 50;
            spawnPos.y -= 80;
        }
        if (lastDepIsLeft == true) {
            spawnPos.x -= 50;
            spawnPos.y -= 40;
        }
        AudioManager::getInstance().playSound("tirE");
        
        Projectile newProjectile(Shared::projMini, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
        newProjectile.resize(50, 25);
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
