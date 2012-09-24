#ifndef PROJECTILE_MANAGER_H_INCLUDED
#define PROJECTILE_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "projectile.h"
#include "missile.h"

class Projectile_manager
{
    public:
        Projectile_manager(sf::RenderWindow &app);

        //Destructeur
        ~Projectile_manager();

        //Vérifie si il y a des projectiles en cours
        bool haveEnemyProjectilesInProgress();
        bool havePlayerProjectilesInProgress();

        //Déplace tous les projectiles
        void moveProjectile();

        //Dessine tous les projectiles
        void drawProjectile();

        //Rajoute un projectile dans la liste des projectiles ennemi
        void addEnemyProjectile(Projectile* projectile);

        //Rajoute un projectile dans la liste des projectiles joueur
        void addPlayerProjectile(Projectile* projectile);

        //Retourne les projectiles ennemi
        std::list<Projectile*>* getEnemyProjectiles();

        //Retourne les projectiles joueur
        std::list<Projectile*>* getPlayerProjectiles();

    private:
        //La fenêtre
        sf::RenderWindow &m_app;

        //Liste des projectiles ennemis
        std::list<Projectile*> m_enemyProjectiles;

        //Liste des projectiles du joueur
        std::list<Projectile*> m_playerProjectiles;

        //Liste des missiles
        std::list<Missile*> m_missiles;
};

#endif // PROJECTILE_MANAGER_H_INCLUDED
