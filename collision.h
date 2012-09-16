#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "population.h"
#include "projectile_manager.h"
#include "tirs/missile_manager.h"
#include "drop.h"

//Gère les collisions des types unit

class Collision
{
    public:
        Collision(sf::Vector2f windowSize, Player &player, Population &population, Projectile_manager &projectile_manager, Missile_manager &missile_manager, Drop_manager &drop_manager);
        virtual ~Collision();
        void manageCollisionsX();
        void manageCollisionsY();
        void manageProjectileCollision();
        void dropCollision();

    protected:
        Player &m_player;
        Population &m_population;
        const sf::Vector2f m_windowSize;
        Projectile_manager &m_projectile_manager;
        Missile_manager &m_missile_manager;
        Drop_manager &m_drop_manager;

};

bool checkCollision(const sf::IntRect & a, const sf::IntRect & b);

#endif // COLLISION_H_INCLUDED
