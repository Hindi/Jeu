#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>

#include "../player.h"
#include "enemy.h"
#include "../timer.h"

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
             int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport);
        //Destruteur
        virtual ~Boss();

        virtual void draw();
        sf::Vector2f getPosition();
        virtual void setTeleporting(bool state);
        void firinhMahLasor();

        //Variables laser
        bool startingLasor;
        Timer timerAddMove;

    protected:
        const char* m_name;
        const char* m_type;
        short m_level;


};
#endif // BOSS_H_INCLUDED
