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
#include "boss.h"

/*
****************************************
TODO :
    - Fonction follow pour suivre le boss
    - Diff�rents mode de tirs
    - Quels d�placement ?
****************************************
*/

class Adds : public Enemy
{
    public:
        Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f relativePosition, const char* type, const char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport, std::tr1::shared_ptr<Boss> boss);
        ~Adds();

        //Suivre le boss
        void follow();
        virtual void teleport();

    private:
        std::tr1::shared_ptr<Boss> m_boss;
        //Timers de tir et de d�placement
        Timer timer, timerMove;

        sf::Vector2f relativePosition;

        //Sauvegarde sur un timer de d�placement
        float savedTimerMove;


        short const m_maxLife;


};

#endif // ADDS_H_INCLUDED
