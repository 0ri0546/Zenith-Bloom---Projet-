#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#pragma once

#include "Datas.hpp"
#include "GESTION TEXTURE.hpp"

class Platform {
public:
	TextureManager textureManager;
	const sf::Texture& platformTexture = textureManager.getTexture("C:/Users/ceury/source/repos/0ri0546/Zenith-Bloom---Projet-/ASSETS/Srite Test/bob.jpg");

	Platform(float x, float y);
	void addPlatform(float x, float y);
	sf::Sprite getSprite() const;
	

private:
	sf::Sprite spritePlatforme; 
	
	float scalePlateform =1 ;
};


#endif

