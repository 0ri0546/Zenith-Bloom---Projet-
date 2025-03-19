#ifndef SOUND_MENU_HPP
#define SOUND_MENU_HPP

#include "Menu.hpp"
#include "../../systems/AudioSystem.hpp"

class SoundMenu : public Menu {
private: 
AudioSystem audioSystem; 

void initButtons() override; 

public: 
	SoundMenu(); 

	int handleInput(sf::RenderWindow& window, const sf::Event& event) override; 
	void updateSliderValues(); 
}; 

#endif // SOUND_MENU_HPP