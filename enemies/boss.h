#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>

#include "../player.h"
#include "enemy.h"
#include "adds.h"

/*
****************************************
TODO :
    - Fonction pour cr�er les adds
****************************************
*/
class Boss : public Enemy
{
    public:
        Boss(int life, int scoreHit, int scoreExplosion,  int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod,
             int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        //Destruteur
        ~Boss();

        sf::IntRect getBoundingBox();
        sf::IntRect getWeakBox();

        void draw();

    protected:
        std::list<std::tr1::shared_ptr<Adds> > m_adds;
        const char* m_name;
        short m_level;


};
#endif // BOSS_H_INCLUDED
