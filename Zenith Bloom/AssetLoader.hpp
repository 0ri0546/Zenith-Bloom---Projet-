#pragma once

#include "Datas.hpp"

class Assets {
public:
	Assets();
	void resize(sf::Sprite& sprite, float scaleX, float scaleY);
private:
	void loadAssetsFromFiles();
	
};