#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <tr1/memory>

#include "player.h"
#include "population.h"
#include "tirs/projectile_manager.h"
#include "tirs/missile_manager.h"
#include "drop.h"
#include "enemies/spawn.h"

//G�re les collisions des types unit

class Collision
{
    public:
        Collision(sf::Vector2f windowSize, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);

        //Destructeur
        virtual ~Collision();

        //Collisions d�placement joueur
        void manageCollisionsX();
        void manageCollisionsY();

        void manageCollisionsX2();
        void manageCollisionsY2();

        //Collisions sur les tirs
        void manageProjectileCollision();

        //Collisions sur les drops
        void dropCollision();

    protected:
    //Objet joueur
        std::tr1::shared_ptr<Player> m_player, m_player2;

        sf::SoundBuffer clingBuffer;
        sf::Sound clingSound;

        //Taille de la fen�tre
        const sf::Vector2f m_windowSize;
};

//V�rifie les colisions entre rectangles
bool checkCollision(const sf::IntRect & a, const sf::IntRect & b);

#endif // COLLISION_H_INCLUDED
