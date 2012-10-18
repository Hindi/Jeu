#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "animation.h"
#include "Animated.hpp"
#include "image_manager.h"
#include "const.h"
#include "timer.h"

//class m�re des unit�s de jeu (player, enemy)

class Unit
{
    public:
        Unit(int life, int xSpeed, int ySpeed, sf::Vector2f position);

        //Destructeur
         ~Unit();

        //Accesseur sur les hp restants
         short getLife();

        //Re�oit des dommages
         void recieveDamages(int dmg);

        //D�finit s'i lest mort ou non
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

         void startAnimTimer();

    protected:
        //Variables d'animation
        Anim m_animExplosion;
        Animated *m_animatedExplosion;

        //Echelle d'affichage
        const sf::Vector2f m_scale;

        //Taille de l'explosion
        int const EXPLOS_WIDTH, EXPLOS_HEIGHT;

        //La position courante
        sf::Vector2f m_position;

        //Le sprite
        sf::Sprite sprite;

        //L'image de l'explosion
        sf::Image *imageExplosion;

        //Les hp qui restent
        short m_life;

        // Vitesses sur chaque axe
        short m_xSpeed, m_ySpeed;

        //Le coeficient de vitesse
        short coefSpeed;

        //Le frame courant
        short currentFrameX, currentFrameY;

        Timer animExplosion;
};

#endif // UNIT_H_INCLUDED
