#include <iostream>
#include <SFML/Graphics.hpp> 

using namespace std; 


class Entity
{
public : 
	Entity(); 
	virtual ~Entity() = 0; 

	virtual void draw(sf::RenderWindow& window) = 0;



};