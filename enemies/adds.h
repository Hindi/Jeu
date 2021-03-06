#ifndef ADDS_H_INCLUDED
#define ADDS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "../player.h"
#include "../timer.h"
#include "../tirs/projectile.h"
#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "../tirs/projectile_manager.h"
#include "../const.h"
#include "enemy.h"

/*
****************************************
TODO :
    - Fonction follow pour suivre le boss
    - Différents mode de tirs
    - Quels déplacement ?
****************************************
*/

class Adds : public Enemy
{
    public:
        Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f relativePosition, sf::Vector2f absolutePosition,const char* type, const char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport);
        ~Adds();

        //Suivre le boss
        virtual void teleport();
        sf::Vector2f getRelativePosition();
        void horizontalMove(int speed);

    private:
        //Timers de tir et de déplacement
        Timer timer, timerMove;

        sf::Vector2f relativePosition;
        sf::IntRect getBoundingBox();

        //Sauvegarde sur un timer de déplacement
        float savedTimerMove;


        short const m_maxLife;


};

#endif // ADDS_H_INCLUDED
