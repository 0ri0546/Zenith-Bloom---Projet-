#pragma once

#include "../entities/Tank.hpp"


Tank::Tank(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY) : Ennemy(x, y, text, textR, xT, yT, scaleX, scaleY, textRecX, textRecY) {
	//spriteEnnemy.setTexture(Shared::tankTexture);

	life = 7;
	speed = 0.3;
	currentState = PATROL;
	radiusDetection = 300;
	circle.setRadius(radiusDetection);
	circle.setOrigin(radiusDetection, radiusDetection);

}

void Tank::attack(Player& player, float deltaTime) {
	if (player.getShape().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
        isAttacking = true;
        player.takeDamageSimple(deltaTime);
        if (player.getShape().getPosition().x < spriteEnnemy.getPosition().x) {
            lastDepIsLeft = true;
            AudioManager::getInstance().playSound("hit1");
            attackAnim.update(deltaTime);
		    attackAnim.applyToSprite(spriteEnnemy, 2);
        }
        else {
            lastDepIsLeft = false;
            AudioManager::getInstance().playSound("hit1");
            attackAnimR.update(deltaTime);
            attackAnimR.applyToSprite(spriteEnnemy, 2);
        cout << "attaque";
        }
		
	}
    if (!player.getShape().getGlobalBounds().intersects(spriteEnnemy.getGlobalBounds())) {
        isAttacking = false; // L'ennemi peut rejouer d'autres animations
    }

}

void Tank::runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) {
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
            //collision(player, projectile, ennemies, deltaTime);
            break;
        case SEARCH:


            break;
        case CHASE:
            if (!isAttacking) {
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
            }
            chase(player);
            attack(player, deltaTime);
            //rangedAttack(deltaTime);
            /*attackAnim.update(deltaTime);
            attackAnim.applyToSprite(spriteEnnemy, 0);*/
            break;
        case DEAD:

            break;
        case NIGHT:
            break;
        }
    }

    /*for (auto& detectionCircle : detectionCircles) {
        detectionCircle.setRadius(radiusDetection);
        detectionCircle.setOrigin(radiusDetection, radiusDetection);
        detectionCircle.setFillColor(sf::Color::Black);
        detectionCircle.setPosition(spriteEnnemy.getPosition());
    }*/

    collision(player, projectile, ennemies, deltaTime);
    updateProjectiles(deltaTime, window);


    //fillEmptySpacesWithShadows(tiles); // Ombres
    //window.draw(circle);
}
