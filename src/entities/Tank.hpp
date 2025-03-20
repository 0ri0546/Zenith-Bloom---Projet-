#pragma once

#include "../entities/FSM.hpp"


class Tank : public Ennemy {
public :
	Tank(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	//float life = 5;

	void attack(Player& player, float deltaTime);

	void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) override;
private : 
	bool isAttacking = false;

};