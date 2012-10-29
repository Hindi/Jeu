#ifndef ADDS_H_INCLUDED
#define ADDS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>

#include "../player.h"
#include "../timer.h"
#include "../unit.h"
#include "../tirs/projectile.h"
#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "../tirs/projectile_manager.h"
#include "Enemy.h"

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
              const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        ~Adds();

        //Suivre le boss
        void follow(sf::Vector2f speed);

        //Accesseur sur le sprite
        sf::Sprite* getSprite();

        void follow();


    private:
        //Liste des projectiles du boss
        std::list<Projectile*> m_projectiles;

        //Liste des vitesses de tous les projectiles
        std::list<sf::Vector2f> m_vitesses;

        //Direction de déplacement
        char* direction;

        //Le moment du dernier tir
        float lastShot;

        //Timers de tir et de déplacement
        Timer timer, timerMove;

        //Sauvegarde sur un timer de déplacement
        float savedTimerMove;

        //Position du joueur
        sf::Vector2f playerPosition;

        short const m_maxLife;


};

#endif // ADDS_H_INCLUDED
