#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "animation.h"
#include "Animated.hpp"
#include "tirs/projectile_manager.h"
#include "image_manager.h"

//class mère des unités de jeu (player, enemy)

class Unit
{
    public:
        Unit(int life, int xSpeed, int ySpeed, sf::Vector2f position, image_manager &imageManager);

        //Destructeur
         ~Unit();

        //Accesseur sur les hp restants
         short getLife();

        //Reçoit des dommages
         void recieveDamages(int dmg);

        //Définit s'i lest mort ou non
         bool isDead();

        //Dessine l'explosion
         void drawExplosion();

        //Accsseur sur la taille de l'explosion
         int getExploWidth() const;
         int getExploHeight() const;

        //Accesseur sur la vitesse
         sf::Vector2f getSpeed();

        //Accesseur sur le coeficient de vitesse
         short getCoefSpeed() const;

    protected:
        //Variables d'animation
        Anim m_animExplosion;
        Animated *m_animatedExplosion;

        //Echelle d'affichage
        const sf::Vector2f m_scale;

        //Taille de l'explosion
        int const EXPLOS_WIDTH, EXPLOS_HEIGHT;

        //La fenêtre
        sf::RenderWindow &m_app;

        //La position courante
        sf::Vector2f m_position;

        //Le sprite
        sf::Sprite sprite;

        //L'image de l'explosion
        sf::Image *imageExplosion;

        //Les hp qui restent
        short m_life;

        // Vitesses sur chaque axe
        short const m_xSpeed, m_ySpeed;

        //Le coeficient de vitesse
        short coefSpeed;

        //Le frame courant
        short currentFrameX, currentFrameY;

        //Manager de projectiles
        Projectile_manager &m_projectile_manager;

        image_manager &m_imageManager;
};

#endif // UNIT_H_INCLUDED
