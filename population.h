#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "projectile.h"
#include "projectile_manager.h"
#include "drop_manager.h"
#include "enemies/boss.h"
#include "player.h"
#include "image_manager.h"

//Permet de stocker et g�rer les ennemis

class Population
{
    public:
        Population(sf::RenderWindow &app, Projectile_manager &projectile_manager, Drop_manager &drop_manager, Player &player, image_manager &imageManager);

        //Destructeur
        virtual ~Population();

        //Liste des ennemis
        std::list<Enemy*>* getPopulation();

        //V�rifie si des ennemis sont en vie
        bool haveEnnemyInProgress();

        //Permet de dessiner les ennemis et les projectiles
        void drawPopulation();

        //V�rifie l'�tat des ennemis et des projectiles
        void checkPopulation();

        //Met le jeu en pause
        void freeze();

        //Sort le jeu de sa pause
        void unFreeze();

        //Cr�ateurs d'ennemis
        void createShip(sf::Vector2f position, char* move);
        void createFlyingSaucer(sf::Vector2f position, char* move);

        //Fait exploser un ennemi
        void explode(Enemy *enemy);

        //Fait evoluer l'animaton de l'explosion
        void manageExplosion();

        //G�re les fonctions de mise � jour
        void manage();

        //Cr�ation d'un boos
        void createBoss(sf::Vector2f position, char* move, char* name);


    protected:
        //La fen�tre
        sf::RenderWindow &m_app;

        //Le joueur
        Player &m_player;

        //Manager d'images
        image_manager &m_imageManager;

        //Liste des ennemis
        std::list<Enemy*> m_enemies;

        //Liste des ennemis morts
        std::list<Enemy*> m_deadEnemies;

        //Manager de projectiles
        Projectile_manager &m_projectile_manager;

        //Manager de drops
        Drop_manager &m_drop_manager;

};

#endif // POPULATION_H_INCLUDED
