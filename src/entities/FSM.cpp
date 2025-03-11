#include "FSM.hpp"

Ennemy::Ennemy()
{

	spriteEnnemy.setTexture(Shared::ennemyTexture);
	assets.resize(spriteEnnemy, 100, 100);
	spriteEnnemy.setOrigin(spriteEnnemy.getLocalBounds().width / 2, spriteEnnemy.getLocalBounds().height / 2);

	spriteEnnemy.setPosition(250, 50);
	
	currentState = PATROL;
	detectionCircle.setRadius(radiusDetection);
	detectionCircle.setOrigin(radiusDetection, radiusDetection);
	detectionCircle.setFillColor(sf::Color::Black);
}

sf::Sprite Ennemy::getSprite() const
{
	return spriteEnnemy;
}

void Ennemy::patrol(Player& player)
{
	const float speed = 2;
	static int currentWaypoint = 0;
	static sf::Vector2f waypoints[2] = { sf::Vector2f(0,400), sf::Vector2f(400, 400) };
	sf::Vector2f target = waypoints[currentWaypoint];


	sf::Vector2f diretion(
		speed * copysign(1.0f, target.x - spriteEnnemy.getPosition().x),
		speed * copysign(1.0f, target.y - spriteEnnemy.getPosition().y)
	);
	//currentWaypoint = (currentWaypoint + 1) % 2;
	spriteEnnemy.move(diretion);

	/*if (spriteEnnemy.getPosition()) {
		 
	}*/
	{
		currentWaypoint = (currentWaypoint + 1) % 2;
	}
	if (player.getShape().getPosition().x - spriteEnnemy.getPosition().x < radiusDetection || player.getShape().getPosition().y - spriteEnnemy.getPosition().y < radiusDetection) {
		currentState = CHASE;
	}
	else {
		currentState = PATROL;

	}
}

void Ennemy::chase(Player& player)
{

	const float speed = 2; 

	sf::Vector2f direction(
		speed * copysign(1.0f, player.getShape().getPosition().x - spriteEnnemy.getPosition().x),
		speed * copysign(1.0f, player.getShape().getPosition().y - spriteEnnemy.getPosition().y)
	);

	spriteEnnemy.move(direction);

	if (player.getShape().getPosition().x - spriteEnnemy.getPosition().x > radiusDetection || player.getShape().getPosition().y - spriteEnnemy.getPosition().y > radiusDetection) {
		currentState = PATROL;
	}

}




void Ennemy::runEnnemy(Player& player, sf::RenderWindow& window)
{


	switch (currentState)
	{
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
	detectionCircle.setPosition(spriteEnnemy.getPosition());
	

	window.draw(detectionCircle);
	window.draw(spriteEnnemy);
}
