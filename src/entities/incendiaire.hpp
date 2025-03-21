#pragma once

#include "../entities/FSM.hpp""


class Incendiaire : public Ennemy {
public:
	Incendiaire(unsigned long long x, unsigned long long y, sf::Texture& text, sf::Texture& textR, float xT, float yT, float scaleX, float scaleY, float textRecX, float textRecY);
	//float life = 5;
	void rangedAttack(float deltaTime) override;

	/*void spawnFlame(); 
	void updateFlames(float deltaTime); 
	void drawFlames(sf::RenderWindow& window); */
	//void runEnnemy(Player& player, sf::RenderWindow& window, std::vector<Projectile>& projectile, vector<std::unique_ptr<Ennemy>>& ennemies, std::vector<std::unique_ptr<Tiles>>& tiles, float deltaTime) override;
	//radiusDetection = 50;
struct Flame {
		sf::Sprite spriteFlame;
		sf::Clock lifetimeClock;
		float lifetime = 1.5f; // Temps avant que la flamme disparaisse
	};
std::vector<Flame> flames;
private : 


	sf::Clock flameSpawnClock; // Horloge pour gérer le spawn des flammes
	float flameSpawnInterval = 3.0f; // Temps en secondes entre chaque spawn

	

	 // Liste des flammes




	//float x, y;

	//Animation attackAnim, walkAnim, standAnim, hitAnim;
};