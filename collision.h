#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.h"
#include "population.h"
#include "tirs/projectile_manager.h"
#include "tirs/missile_manager.h"
#include "drop.h"
#include "enemies/spawn.h"

//Gère les collisions des types unit

class Collision
{
    public:
        Collision(sf::Vector2f windowSize, Player &player,Missile_manager &missile_manager);

        //Destructeur
        virtual ~Collision();

        //Collisions déplacement joueur
        void manageCollisionsX();
        void manageCollisionsY();

        //Collisions sur les tirs
        void manageProjectileCollision();

        //Collisions sur les drops
        void dropCollision();

    protected:
    //Objet joueur
        Player &m_player;

        //Taille de la fenêtre
        const sf::Vector2f m_windowSize;

        //manager de missiles
        Missile_manager &m_missile_manager;


};

//Vérifie les colisions entre rectangles
bool checkCollision(const sf::IntRect & a, const sf::IntRect & b);

#endif // COLLISION_H_INCLUDED
