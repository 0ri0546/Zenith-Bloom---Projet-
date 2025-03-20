#include "../entities/drone.hpp"

Drone::Drone(unsigned long long x, unsigned long long y, sf::Texture text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY)
    : Ennemy(x, y, text, textR, xT, yT, scaleX, scaleY, textRecX, textRecY) {
    spriteEnnemy.setTexture(Shared::droneTexture);
    initialPosition = spriteEnnemy.getPosition(); // Enregistre la position initiale
}

void Drone::attack(Player& player, float deltaTime) {
    if (attackClock.getElapsedTime().asSeconds() >= 0.5f) {
        sf::Vector2f spawnPos = spriteEnnemy.getPosition();
        spawnPos.x += lastDepIsLeft ? -20 : spriteEnnemy.getGlobalBounds().width;
        Projectile newProjectile(Shared::waterProjTexture, sf::Vector2f(spawnPos.x, spawnPos.y), lastDepIsLeft);
        newProjectile.resize(30, 30);
        projectilesDrone.push_back(newProjectile);
        attackClock.restart();
        attackClockDuration.restart();
    }
}

void Drone::runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectiles, std::vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) {
    colEnnemiToGround(ennemies, tiles);

    // Le drone ne subit pas la gravité, donc la vélocitéY n'est pas modifiée.
    // Il est libre de se déplacer sans être affecté par la gravité

    // Déplacement du drone autour de son point d'apparition (comportement de patrouille ou de mouvement libre)
    float movementSpeed = 50.0f; // Vitesse de déplacement
    float amplitudeX = 100.0f;  // Amplitude horizontale du mouvement
    float amplitudeY = 50.0f;   // Amplitude verticale du mouvement

    // Se déplacer autour du point d'apparition en créant un mouvement sinusoïdal pour l'effet de va-et-vient
    float offsetX = amplitudeX * sinf(spriteEnnemy.getPosition().x / 100.0f);  // Déplacement horizontal
    float offsetY = amplitudeY * cosf(spriteEnnemy.getPosition().y / 100.0f);  // Déplacement vertical

    spriteEnnemy.setPosition(initialPosition.x + offsetX, initialPosition.y + offsetY);  // Appliquer le déplacement

    // Détection d'attaque
    attack(player, deltaTime);

    // Animation de l'ennemi
    switch (currentState) {
    case PATROL:
        standAnim.update(deltaTime);
        standAnim.applyToSprite(spriteEnnemy, 0);
        break;
    case SEARCH:
        break;
    case CHASE:
        chase(player);
        break;
    case DEAD:
        break;
    case NIGHT:
        break;
    }

    collision(player, projectiles, ennemies, deltaTime);
    updateProjectiles(deltaTime, window);
}

