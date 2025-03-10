#include "Platform.hpp"

Platform::Platform(float x, float y)
{
	spritePlatforme.setTexture(platformTexture);
	spritePlatforme.setScale(scalePlateform, scalePlateform);
	spritePlatforme.setPosition(x, y);
};

void Platform::addPlatform(float x, float y) {
	
	spritePlatforme.setPosition(x, y);
}
 
sf::Sprite Platform::getSprite() const {
	return spritePlatforme;
}