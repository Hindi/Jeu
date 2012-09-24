#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "animation.h"
#include "Animated.hpp"
#include "tirs/projectile_manager.h"

//class mère des unités de jeu (player, enemy)

class Unit
{
    public:
        Unit(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, Projectile_manager &projectile_manager);

        //Destructeur
        virtual ~Unit();

        //Accesseur sur les hp restants
        virtual int getLife();

        //Reçoit des dommages
        virtual void recieveDamages(int dmg);

        //Définit s'i lest mort ou non
        virtual bool isDead();

        //Dessine l'explosion
        virtual void drawExplosion();

        //Accsseur sur la taille de l'explosion
        virtual int getExploWidth() const;
        virtual int getExploHeight() const;

        //Accesseur sur la vitesse
        virtual sf::Vector2f getSpeed();

        //Accesseur sur le coeficient de vitesse
        virtual int getCoefSpeed() const;

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
        int m_life;

        // Vitesses sur chaque axe
        int m_xSpeed, m_ySpeed;

        //Le coeficient de vitesse
        int const coefSpeed;

        //Le frame courant
        int currentFrameX, currentFrameY;

        //Manager de projectiles
        Projectile_manager &m_projectile_manager;
};

#endif // UNIT_H_INCLUDED
