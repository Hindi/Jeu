#ifndef MEGASPAWNER_H
#define MEGASPAWNER_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../boss.h"
#include "../adds.h"
#include "../../player.h"
#include "../../tirs/projectile.h"
#include "../../image_manager.h"
#include "../../tirs/projectile_manager.h"
#include "../../const.h"
#include "../../timer.h"
#include "../../population.h"

class Megaspawner : public Boss
{
    public:
        Megaspawner(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        //Destruteur
        virtual ~Megaspawner();

        void fire();
        //void follow();
        sf::IntRect getBoundingBox();
        sf::IntRect getWeakBox();
        void move();


    private:
        Timer timerMove;
        short m_level;
        Timer timerRandomShot;


};
#endif // MEGASPAWNER_H
