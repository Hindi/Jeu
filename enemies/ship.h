#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "../player.h"

class Ship : public Enemy
{
    public:
        Ship(sf::Vector2f position, const std::string &move, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);
        ~Ship();

        void fire();

    private:



};


#endif // SHIP_H_INCLUDED
