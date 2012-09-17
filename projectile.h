#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "image_manager.h"
#include <iostream>

//Type projectile géré par player et enemy

class Projectile : public sf::Drawable
{
    public:
        Projectile(const std::string &filepath, sf::Vector2f position, sf::Vector2f speed, const int coefSpeed, image_manager &ImageManager);

        //Destructeur
        ~Projectile();

        //Sprite des projectiles
        sf::Sprite getSprite();

        //Parce que c'est un drawable, permet de les dessiner directement
        void Render(sf::RenderTarget& target) const;

        //Accesseur sur la vitesse
        int getSpeed(int axis) const;

        //Accesseur sur le coeficient de vitesse
        const int getCoefSpeed() const;

        //Accesseur sur le rectangle du sprite
        sf::IntRect getBoundingBox() const;

        //Setter de position
        void setPosition(sf::Vector2f position);

        //Accesseur sur la position
        sf::Vector2f getPosition();

    protected:
        //Image associée au sprite
        sf::Image *image;

        //Le sprite
        sf::Sprite sprite;

        //L'échelle d'affichage des projectiles
        const sf::Vector2f scale;

        //Vitesse des projcetiles
        sf::Vector2f m_speed;

        //Coeficient de vitesse
        const int m_coefSpeed;

        //Taille du sprite
        int m_width, m_height;

        //Position courante
        sf::Vector2f m_position;
};

#endif // PROJECTILE_H_INCLUDED
