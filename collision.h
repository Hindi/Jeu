#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "population.h"
#include "projectile_manager.h"
#include "tirs/missile_manager.h"
#include "drop.h"

//G�re les collisions des types unit

class Collision
{
    public:
        Collision(sf::Vector2f windowSize, Player &player, Population &population, Projectile_manager &projectile_manager, Missile_manager &missile_manager, Drop_manager &drop_manager);

        //Destructeur
        virtual ~Collision();

        //Collisions d�placement joueur
        void manageCollisionsX();
        void manageCollisionsY();

        //Collisions sur les tirs
        void manageProjectileCollision();

        //Collisions sur les drops
        void dropCollision();

    protected:
    //Objet joueur
        Player &m_player;

        //Manager d'ennemis
        Population &m_population;

        //Taille de la fen�tre
        const sf::Vector2f m_windowSize;

        //Manager de projectiles
        Projectile_manager &m_projectile_manager;

        //manager de missiles
        Missile_manager &m_missile_manager;

        //Manager de drops
        Drop_manager &m_drop_manager;

};

//V�rifie les colisions entre rectangles
bool checkCollision(const sf::IntRect & a, const sf::IntRect & b);

#endif // COLLISION_H_INCLUDED
