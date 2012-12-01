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

class Octopus : public Boss
{
    public:
        Octopus(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        virtual ~Octopus();

        void fire();
        //void follow();
        sf::IntRect getBoundingBox();
        sf::IntRect getWeakBox();
        void move();
        void follow();

    private:
        Timer timerMove;
        int lastTentaMove;

};

#endif // OCTOPUS_H
