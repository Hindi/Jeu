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
#include "enemy.h"

class Spawn : public Enemy
{
    public:
        Spawn(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, int moveValue,
              const int coefSpeed, const int firerate);

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
        //timer pour d�placemens al�atoires
        Timer timerMove;

        //Timer pour cadencer les tirs
        Timer timerFire;

        //Moment du dernier movement et tirs
        float lastMove, lastShot;

        //Fr�quence de changemen de direction et fr�quence de tir
        short const moveRate;

        //Angle de d�placement g�n�r� al�atoirement
        unsigned short m_angleMove;

};

#endif // SPAWN_H_INCLUDED
