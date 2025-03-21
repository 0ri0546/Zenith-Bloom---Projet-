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
    flameSpawnClock.restart();
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


//void Incendiaire::spawnFlame() {
//
//    if (flameSpawnClock.getElapsedTime().asSeconds() >= flameSpawnInterval) {
//        Flame newFlame;
//        newFlame.spriteFlame.setTexture(Shared::flame); // Charge la texture
//        newFlame.spriteFlame.setPosition(spriteEnnemy.getPosition().x, spriteEnnemy.getPosition().y ); // Ajuste la position
//        newFlame.spriteFlame.setScale(1.5, 1.5); // Ajuste la taille si besoin
//
//        flames.push_back(newFlame); // Ajoute la flamme à la liste
//        flameSpawnClock.restart(); // Reset le timer
//        cout << "flame" << endl;
//    }
//}
//
//void Incendiaire::updateFlames(float deltaTime) {
//    for (auto it = flames.begin(); it != flames.end();) {
//        if (it->lifetimeClock.getElapsedTime().asSeconds() > it->lifetime) {
//            it = flames.erase(it); // Supprime la flamme si elle a existé assez longtemps
//        }
//        else {
//            ++it;
//        }
//    }
//}
//
//void Incendiaire::drawFlames(sf::RenderWindow& window) {
//    for (const auto& flame : flames) {
//        window.draw(flame.spriteFlame);
//        std::cout << "Flame position : " << flame.spriteFlame.getPosition().x << ", " << flame.spriteFlame.getPosition().y << std::endl;
//    }
//}


//void Incendiaire::runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) {
//
//
//
//
//
//    colEnnemiToGround(ennemies, tiles);
//
//
////spawnFlame();
////updateFlames(deltaTime); // Met à jour la durée de vie des flammes
////            drawFlames(window); // Affiche les flammes
//    if (!onTheGround) {
//
//        velocityY += gravity * deltaTime;
//
//        if (velocityY > maxFallSpeed) {
//            velocityY = maxFallSpeed;
//        }
//
//        spriteEnnemy.move(0, velocityY * deltaTime);
//    }
//    else {
//        velocityY = 0;
//    }
//
//
//
//    colEnnemyToEnnemy(ennemies);
//    colEnnemyToPlayer(player, ennemies);
//    circle.setPosition(spriteEnnemy.getPosition());
//    if (onTheGround) {
//        switch (currentState) {
//        case PATROL:
//
//
//            standAnim.update(deltaTime);
//            standAnim.applyToSprite(spriteEnnemy, 0);
//            patrol(player);
//            //collision(player, projectile, ennemies, deltaTime);
//            break;
//        case SEARCH:
//
//
//            break;
//        case CHASE:
//
//            if (player.getShape().getPosition().x < spriteEnnemy.getPosition().x) {
//                lastDepIsLeft = true;
//                walkAnimR.update(deltaTime);
//                walkAnimR.applyToSprite(spriteEnnemy, 0);
//            }
//            else {
//                lastDepIsLeft = false;
//                walkAnim.update(deltaTime);
//                walkAnim.applyToSprite(spriteEnnemy, 0);
//            }
//
//            
//            
//            chase(player);
//            rangedAttack(deltaTime);
//
//            /*attackAnim.update(deltaTime);
//            attackAnim.applyToSprite(spriteEnnemy, 0);*/
//            break;
//        case DEAD:
//
//            break;
//        case NIGHT:
//            break;
//        }
//    }
//
//    /*for (auto& detectionCircle : detectionCircles) {
//        detectionCircle.setRadius(radiusDetection);
//        detectionCircle.setOrigin(radiusDetection, radiusDetection);
//        detectionCircle.setFillColor(sf::Color::Black);
//        detectionCircle.setPosition(spriteEnnemy.getPosition());
//    }*/
//
//    collision(player, projectile, ennemies, deltaTime);
//    updateProjectiles(deltaTime, window);
//
//
//    //fillEmptySpacesWithShadows(tiles); // Ombres
//    //window.draw(circle);
//
//}