#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "enemies/enemy.h"
#include "tirs/projectile.h"
#include "tirs/projectile_manager.h"
#include "drop_manager.h"
#include "enemies/boss.h"
#include "player.h"
#include "image_manager.h"
#include "enemies/spawn.h"
#include "tirs/score_manager.h"
#include "Anim.hpp"
#include "const.h"

//Permet de stocker et gérer les ennemis

class Population
{
    public:
        //Liste des ennemis
        std::list<Enemy*>* getPopulation();

        //Vérifie si des ennemis sont en vie
        bool haveEnnemyInProgress();

        //Permet de dessiner les ennemis et les projectiles
        void drawPopulation();

        //Vérifie l'état des ennemis et des projectiles
        void checkPopulation();

        //Met le jeu en pause
        void freeze();

        //Sort le jeu de sa pause
        void unFreeze();

        //Créateurs d'ennemis
        void createShip(sf::Vector2f position, char* move, bool spawner = false);
        void createFlyingSaucer(sf::Vector2f position, char* move, bool spawner = false);

        //Fait exploser un ennemi
        void explode(Enemy *enemy);

        //Fait exploser un spawn
        void explode(Spawn *spawn);

        //Fait evoluer l'animaton de l'explosion
        void manageExplosion();

        //Gère les fonctions de mise à jour
        void manage();

        //Création d'un boos
        void createBoss(sf::Vector2f position, char* move, char* name);

        //Vérifient qu'il y a des spawn en jeu
        bool haveSpawnInProgress();

        void spawn(Enemy *enemy);

        static void kill();
        static Population* getInstance();
        void setPlayer(Player *externPlayer);

    protected:
        //Liste des ennemis
        std::list<Enemy*> m_enemies;
        std::list<Enemy*> m_spawns;

        //Liste des ennemis morts
        std::list<Enemy*> m_deadEnemies;

        Player *player;

    private:
        //Constructeur privé pour singleton
        Population();

        //Destructeur
        virtual ~Population();

        static Population* _singleton;

};


#endif // POPULATION_H_INCLUDED
