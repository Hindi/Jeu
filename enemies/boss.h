#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>

#include "../player.h"
#include "enemy.h"
#include "../timer.h"
#include "adds.h"

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

        sf::IntRect getBoundingBox();
        sf::IntRect getWeakBox();



        void drawAdds();
        virtual void draw();
        void follow();
        virtual void addsMove();
        sf::Vector2f getPosition();
        bool canTeleport();
        void setTeleporting(bool state);
        bool readyToTeleport();
        void teleport();

    protected:
        std::list<std::tr1::shared_ptr<Adds> > m_adds;
        const char* m_name;
        const char* m_type;
        short m_level;
        bool teleporting, allowTeleport;
        int teleportFrame;
        Timer teleportTimer;


};
#endif // BOSS_H_INCLUDED
