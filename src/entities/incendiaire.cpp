#include "../entities/incendiaire.hpp"


Incendiaire::Incendiaire(unsigned long long x, unsigned long long y, sf::Texture& text, float xT, float yT) : Ennemy(x, y, text, xT, yT)
{
	life = 5; 
	speed = 0.5;
	currentState = CHASE;
	radiusDetection = 100;
	circle.setRadius(radiusDetection);
	circle.setOrigin(radiusDetection, radiusDetection);
}