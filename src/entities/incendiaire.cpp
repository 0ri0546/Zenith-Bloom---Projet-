#include "../entities/incendiaire.hpp"


Incendiaire::Incendiaire(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY) : Ennemy(x, y, text, textR, xT, yT, scaleX, scaleY, textRecX, textRecY)
{

	
	//assets.resize(spriteEnnemy, 100, 100);
	life = 5; 
	speed = 0.5;
	//currentState = CHASE;
	radiusDetection = 100;
	circle.setRadius(radiusDetection);
	circle.setOrigin(radiusDetection, radiusDetection);
}