#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "player.h"
#include "population.h"

//Gère les collisions des types unit

class Collision
{
    public:
        Collision(sf::Vector2f windowSize, Player &player, Population &population);
        virtual ~Collision();
        void manageCollisionsX();
        void manageCollisionsY();
        void manageProjectileCollision();

    protected:
        Player &m_player;
        Population &m_population;
        const sf::Vector2f m_windowSize;
};

bool checkCollision(const sf::IntRect & a, const sf::IntRect & b);

#endif // COLLISION_H_INCLUDED
