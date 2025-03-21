#include "../entities/incendiaire.hpp"


Incendiaire::Incendiaire(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY) : Ennemy(x, y, text, textR, xT, yT, scaleX, scaleY, textRecX, textRecY)
{

	
	//assets.resize(spriteEnnemy, 100, 100);
	life = 5; 
	speed = 0.5;
	//currentState = CHASE;
	radiusDetection = 500;
	circle.setRadius(radiusDetection);
	circle.setOrigin(radiusDetection, radiusDetection);
}

void Incendiaire::rangedAttack(float deltaTime) {
    if (rangedAttackClock.getElapsedTime().asSeconds() >= 1.5f) {
        //takeDamageClock.getElapsedTime().asSeconds();
        //rangClock.restart();
        sf::Vector2f spawnPos = spriteEnnemy.getPosition();
        if (lastDepIsLeft == false) {

            spawnPos.x += 80;
            spawnPos.y -= 90;
        }
        if (lastDepIsLeft == true)
        {
            //sf::Vector2f spawnPos = spriteEnnemy.getPosition();
            spawnPos.x -= 50;
            spawnPos.y -= 40;
        }

        AudioManager::getInstance().playSound("tirIcend");

        Projectile newProjectile(Shared::projIcend, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
        newProjectile.resize(50, 25);
        projectiles.push_back(newProjectile);

        /*if (rangClock.getElapsedTime().asSeconds() <= 0.5f) {

            attackAnim.update(deltaTime);
            attackAnim.applyToSprite(spriteEnnemy, 0);

        }*/

        rangedAttackClock.restart();
    }
}
