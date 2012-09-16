#ifndef PROJECTILE_MANAGER_H_INCLUDED
#define PROJECTILE_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "projectile.h"
#include "tirs/missile.h"

class Projectile_manager
{
    public:
        Projectile_manager(sf::RenderWindow &app);
        ~Projectile_manager();
        bool haveEnemyProjectilesInProgress();//Vérifie si il y a des projectiles en cours
        bool havePlayerProjectilesInProgress();

        void moveProjectile();//Déplace tous les projectiles
        void drawProjectile();//Dessine tous les projectiles

        void addEnemyProjectile(Projectile* projectile);//Rajoute un projectile dans la liste des projectiles ennemi
        void addPlayerProjectile(Projectile* projectile);//Rajoute un projectile dans la liste des projectiles joueur

        std::list<Projectile*>* getEnemyProjectiles();//Retourne les projectiles ennemi
        std::list<Projectile*>* getPlayerProjectiles();//Retourne les projectiles joueur

    private:
        sf::RenderWindow &m_app;
        std::list<Projectile*> m_enemyProjectiles;
        std::list<Projectile*> m_playerProjectiles;
        std::list<Missile*> m_missiles;
};

#endif // PROJECTILE_MANAGER_H_INCLUDED
