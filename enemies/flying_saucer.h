#ifndef FLYING_SAUCER_H_INCLUDED
#define FLYING_SAUCER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "../player.h"

class FlyingSaucer : public Enemy
{
    public:
        FlyingSaucer(sf::Vector2f position, const std::string &move, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        ~FlyingSaucer();

        void fire();

    private:



};

#endif // FLYING_SAUCER_H_INCLUDED
