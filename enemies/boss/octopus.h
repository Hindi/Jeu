#ifndef OCTOPUS_H
#define OCTOPUS_H

#include <list>
#include <SFML/Graphics.hpp>

#include "../boss.h"
#include "../adds.h"
#include "../../player.h"
#include "../../tirs/projectile.h"
#include "../../tirs/projectile_manager.h"
#include "../../image_manager.h"
#include "../../const.h"
#include "../../timer.h"
#include "../../Animated.hpp"
#include "../../Anim.hpp"


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
        //Variables d'animation
        Animated *animated, *animated2, *animated3, *animated4, *animated5, *animated6, *animated7;
        Anim anim;
        sf::Image *image;

        Timer timerMove;
        int lastTentaMove;
        bool lasorUp;

};

#endif // OCTOPUS_H
