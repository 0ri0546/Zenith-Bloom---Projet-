#ifndef SHADOW_HPP
#define SHADOW_HPP

#include <SFML/Graphics.hpp>

class Shadow : public sf::RectangleShape {
public:
    // Constructeur
    Shadow(const sf::Vector2f& size, float x, float y);

    // Méthode pour mettre à jour la position de l'ombre
    void setPosition(const sf::Vector2f& position);

    // Méthode pour changer la taille de l'ombre
    void setSize(const sf::Vector2f& size);

private:
    void updateShadowAppearance();
};

#endif 
