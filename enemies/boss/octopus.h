#ifndef OCTOPUS_H
#define OCTOPUS_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../boss.h"
#include "../adds.h"
#include "../../player.h"
#include "../../tirs/projectile.h"
#include "../../tirs/projectile_manager.h"
#include "../../const.h"
#include "../../timer.h"

class octopus
{
    public:
        octopus(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        virtual ~octopus();

        void fire();
        //void follow();
        sf::IntRect getBoundingBox();
        sf::IntRect getWeakBox();
        void move();

    private:
        Timer timerMove;

};

#endif // OCTOPUS_H
