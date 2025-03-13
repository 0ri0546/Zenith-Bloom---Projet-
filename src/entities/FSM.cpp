#include "FSM.hpp"

Ennemy::Ennemy(unsigned long long x, unsigned long long y) : x(x), y(y)
{

	spriteEnnemy.setTexture(Shared::ennemyTexture);
	assets.resize(spriteEnnemy, 100, 100);
	spriteEnnemy.setOrigin(spriteEnnemy.getLocalBounds().width / 2, spriteEnnemy.getLocalBounds().height / 2);

	spriteEnnemy.setPosition(x, y);
	
	currentState = CHASE;

}

sf::Sprite Ennemy::getSprite() const
{
	return spriteEnnemy;
}

void Ennemy::patrol(Player& player)
{

	
	
	/*{
		currentWaypoint = (currentWaypoint + 1) % 2;
	}*/
	/*if (player.getShape().getPosition().x - spriteEnnemy.getPosition().x < radiusDetection || player.getShape().getPosition().y - spriteEnnemy.getPosition().y < radiusDetection) {
		currentState = CHASE;
	}
	else {
		currentState = PATROL;

	}
	*/
	
	/*if (abs(player.getShape().getPosition().x - spriteEnnemy.getPosition().x < radiusDetection) && abs(player.getShape().getPosition().y - spriteEnnemy.getPosition().y < radiusDetection)) {
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








void Ennemy::chase(Player& player)
{
	cout << "chase" << endl;
	const float speed = 1; 
	
	sf::Vector2f direction(
		speed * copysign(1.0f, player.getShape().getPosition().x - spriteEnnemy.getPosition().x),
		speed * copysign(1.0f, player.getShape().getPosition().y - spriteEnnemy.getPosition().y));
		

		spriteEnnemy.move(direction);


		/*if (player.getShape().getGlobalBounds().intersects(spritEnnemies.getGlobalBounds())) {
			currentState = CHASE;
		}
		else {
			currentState = PATROL;
		}*/
	

	//for (auto& detectionCircles : detectionCircles) {
	//	if (player.getShape().getGlobalBounds().intersects(spritEnnemies.getGlobalBounds())) {
	//		currentState = CHASE;
	//	}
	//	else {
	//		currentState = PATROL;
	//	}
	//}
	

}



void Ennemy::runEnnemy(Player& player, sf::RenderWindow& window)
{

	cout << "runEnnemy" << endl;
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
	for (auto& detectionCircles : detectionCircles) {

		detectionCircles.setRadius(radiusDetection);
		detectionCircles.setOrigin(radiusDetection, radiusDetection);
		detectionCircles.setFillColor(sf::Color::Black);

		for (auto& spritEnnemies : spritEnnemies) {

			//detectionCircles.setPosition(spritEnnemies.getPosition());
			//detectionCircles.setOrigin(spritEnnemies.getOrigin());

		}
	}
	
	//cout << currentState << endl;

	//detectionCircle.setPosition(spriteEnnemy.getPosition());
	

	/*window.draw(detectionCircle);
	window.draw(spriteEnnemy);*/
}



void Ennemy::draw(sf::RenderWindow& window)
{
	for (auto& detectionCircles : detectionCircles) {
		window.draw(detectionCircles);
	}
	for (auto& spritEnnemies : spritEnnemies){

		window.draw(spritEnnemies);
	}
}