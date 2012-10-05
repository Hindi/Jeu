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
              const int coefSpeed, const int firerate, bool spawner);
        ~Adds();

        //Suivre le boss
        void follow();

        //Accesseur sur le sprite
        sf::Sprite* getSprite();


    private:
        //Liste des projectiles du boss
        std::list<Projectile*> m_projectiles;

        //Liste des vitesses de tous les projectiles
        std::list<sf::Vector2f> m_vitesses;

        //Direction de déplacement
        char* direction;

        //Porjectile
        Projectile *projectile;

        //Li'mage du boss
        sf::Image *image;

        //Sprite du boss
        sf::Sprite sprite;

        //Le moment du dernier tir
        float lastShot;

        //Timers de tir et de déplacement
        Timer timer, timerMove;

        //Sauvegarde sur un timer de déplacement
        float savedTimerMove;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        //Position du joueur
        sf::Vector2f playerPosition;

        short const m_maxLife;


};

#endif // ADDS_H_INCLUDED
