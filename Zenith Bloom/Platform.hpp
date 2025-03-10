#ifndef PLATFORM_HPP
#define PLATFORM_HPP
#pragma once

#include "Datas.hpp"
#include "GESTION TEXTURE.hpp"
#include "AssetLoader.hpp"

class Platform {
public:
	

	Platform(float x, float y, float width, float height);
	
	sf::Sprite getSprite() const;

	Assets assets;

private:
	sf::Sprite spritePlatform; 
	
	float scalePlateform = 1 ;
};


#endif

