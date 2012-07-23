#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "projectile.h"
#include "projectile_manager.h"
#include "drop_manager.h"

//Permet de stocker et gérer les ennemis

class Population
{
    public:
        Population(sf::RenderWindow &app, Projectile_manager &projectile_manager, Drop_manager &drop_manager);
        virtual ~Population();
        std::list<Enemy*>* getPopulation();
        bool haveEnnemyInProgress();//Vérifie si des ennemis sont en vie
        void drawPopulation();//Permet de dessiner les ennemis et les projectiles
        void checkPopulation();//Vérifie l'état des ennemis et des projectiles
        void freeze();
        void unFreeze();
        void createShip(sf::Vector2f position, Player &player, image_manager &imageManager);//Créé un ennemi de type ship
        void createFlyingSaucer(sf::Vector2f position, Player &player, image_manager &imageManager);
        void explode(Enemy *enemy);//Fait exploser un ennemi
        void manageExplosion();//Fait evoluer l'animaton de l'explosion
        void manage();


    protected:
        sf::RenderWindow &m_app;
        std::list<Enemy*> m_enemies;
        std::list<Enemy*> m_deadEnemies;
        Projectile_manager &m_projectile_manager;
        Drop_manager &m_drop_manager;
};

#endif // POPULATION_H_INCLUDED
