#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include "../player.h"
#include "../timer.h"
#include "../unit.h"
#include "../tirs/projectile.h"
#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "../tirs/projectile_manager.h"
#include "adds.h"
#include "enemy.h"

/*
****************************************
TODO :
    - Fonction pour créer les adds
****************************************
*/
class Boss : public Enemy
{
    public:
        Boss(int life, int scoreHit, int scoreExplosion,  int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod,
             int moveValue, const int coefSpeed, const int firerate, const char* name);
        //Destruteur
        ~Boss();

        void createAdd();

    private:
    std::list<Adds*> m_adds;
    const char* m_name;

};
#endif // BOSS_H_INCLUDED
