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
        Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport);
        ~Adds();

        //Suivre le boss
        void follow(sf::Vector2f speed);

        //Accesseur sur le sprite
        sf::Sprite* getSprite();

        void draw();
        Animated* getAnimation();

    private:
        sf::Image *image;

        //Timers de tir et de déplacement
        Timer timer, timerMove;

        //Sauvegarde sur un timer de déplacement
        float savedTimerMove;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        short const m_maxLife;


};

#endif // ADDS_H_INCLUDED
