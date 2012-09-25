#ifndef SPAWN_H_INCLUDED
#define SPAWN_H_INCLUDED

#include <list>
#include <string>
#include <SFML/Graphics.hpp>

#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "../tirs/projectile_manager.h"
#include "../tirs/projectile.h"
#include "math.h"

#include "../unit.h"
#include "../timer.h"
#include "../player.h"

class Spawn : public Unit
{
    public:
        Spawn(image_manager &imageManager, sf:: Vector2f position, sf::RenderWindow &app, Projectile_manager &projectile_manager, Player &player);

        //Destructeur
        ~Spawn();

        //Pour tirer
        void fire();

        //Pour bouger
        void move();

        //Pour aficherl 'objet � l'�cran
        void draw();

        sf::IntRect getBoundingBox();

        sf::Vector2f getPosition();

    private:
        sf::RenderWindow &m_app;

        Player &m_player;

        //L'image du spawn
        sf::Image *image;

        //Le manager d'image
        image_manager &m_imageManager;

        //Position courante
        sf:: Vector2f m_position;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        //timer pour d�placemens al�atoires
        Timer timerMove;

        //Timer pour cadencer les tirs
        Timer timerFire;

        //Moment du dernier movement et tirs
        int lastMove, lastShot;

        //Fr�quence de changemen de direction et fr�quence de tir
        const int moveRate, fireRate;

        //Angle de d�placement g�n�r� al�atoirement
        int m_angleMove;

        //Objet projectile tir� par les spawn
        Projectile *projectile;

        //Vitesse des proejctiles
        const int projectileSpeed;

};

#endif // SPAWN_H_INCLUDED
