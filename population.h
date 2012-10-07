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

//Permet de stocker et g�rer les ennemis

class Population
{
    public:
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
        void createShip(sf::Vector2f position, char* move, bool spawner = false);
        void createFlyingSaucer(sf::Vector2f position, char* move, bool spawner = false);

        //Fait exploser un ennemi
        void explode(Enemy *enemy);

        //Fait exploser un spawn
        void explode(Spawn *spawn);

        //Fait evoluer l'animaton de l'explosion
        void manageExplosion();

        //G�re les fonctions de mise � jour
        void manage();

        //Cr�ation d'un boos
        void createBoss(sf::Vector2f position, char* move, char* name);

        //V�rifient qu'il y a des spawn en jeu
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
        //Constructeur priv� pour singleton
        Population();

        //Destructeur
        virtual ~Population();

        static Population* _singleton;

};


#endif // POPULATION_H_INCLUDED
