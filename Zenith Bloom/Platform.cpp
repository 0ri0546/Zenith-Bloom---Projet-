#include "Platform.hpp"

Platform::Platform(float x, float y, float width, float height)
{
	Assets assets;
	//assets.resize(Shared::groundSprite, width, height);
	spritePlatform.setTexture(Shared::groundTexture);
	assets.resize(spritePlatform, width, height);
	
	spritePlatform.setPosition(x, y);
};


 
sf::Sprite Platform::getSprite() const {
	return spritePlatform;
}