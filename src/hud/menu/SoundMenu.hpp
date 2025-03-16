#ifndef SOUND_MENU_HPP
#define SOUND_MENU_HPP

#include "Menu.hpp"
#include "Slider.hpp"
#include "../../systems/AudioSystem.hpp"

class SoundMenu : public Menu {
private: 
Slider* mainVolumeSlider; 
Slider* musicVolumeSlider; 
Slider* sfxVolumeSlider; 

AudioSystem audioSystem; 

void initSliders(); 
void initButtons() override; 

public: 
	SoundMenu(); 
	~SoundMenu(); 

	int handleInput(sf::RenderWindow& window, const sf::Event& event) override; 
	void renderSliders(sf::RenderWindow& window); 
	void updateSliderValues(); }; 

#endif // SOUND_MENU_HPP