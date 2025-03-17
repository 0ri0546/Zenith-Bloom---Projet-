#include "../entities/incendiaire.hpp"


Incendiaire::Incendiaire(unsigned long long x, unsigned long long y) : Ennemy(x, y) { 

	spriteEnnemy.setTexture(Shared::incendTexture); 
	life = 5; 
	speed = 0.5;
	currentState = PATROL;
	radiusDetection = 100;
	circle.setRadius(radiusDetection);
	circle.setOrigin(radiusDetection, radiusDetection);
}