#include "ennemy.hpp"

Ennemy::Ennemy(float x, float y)
{
	spriteEnnemy.setTexture(Shared::ennemyTexture);
	assets.resize(spriteEnnemy, 50, 50);

	spriteEnnemy.setPosition(x, y);
}

sf::Sprite Ennemy::getSprite() const
{
	return spriteEnnemy;
}
