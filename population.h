#ifndef POPULATION_H_INCLUDED
#define POPULATION_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include <tr1/memory>

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
#include "timer.h"
#include "enemies/boss/lilith.h"
#include "enemies/adds.h"
#include "enemies/ship.h"
#include "enemies/flying_saucer.h"

//Permet de stocker et gérer les ennemis

class Population
{
    public:
        //Liste des ennemis
        std::list<std::tr1::shared_ptr<Enemy> >* getPopulation();
        std::list<std::tr1::shared_ptr<Boss> >* getBossPopulation();

        //Vérifie si des ennemis sont en vie
        bool haveEnnemyInProgress();

        //Permet de dessiner les ennemis et les projectiles
        void drawPopulation();

        //Vérifie l'état des ennemis et des projectiles
        void checkPopulation();

        //Met le jeu en pause
        void stop();

        //Sort le jeu de sa pause
        void unStop();

        //Créateurs d'ennemis
        void createShip(sf::Vector2f position, const std::string &filepath);
        void createFlyingSaucer(sf::Vector2f position, const std::string &filepath);
        void createSpawner(sf::Vector2f position, const std::string &filepath);

        void createAdd(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, const char* const type, const char* const moveMethod, int moveValue,
              const int coefSpeed, const int firerate,bool spawner, std::tr1::shared_ptr<Player> externPlayer, std::tr1::shared_ptr<Player> externPlayer2);

        //Fait exploser un ennemi
        void explode(std::tr1::shared_ptr<Enemy> enemy);

        //Fait evoluer l'animaton de l'explosion
        void manageExplosion();

        //Gère les fonctions de mise à jour
        void manage();

        //Création d'un boos
        void createLilith();

        //Vérifient qu'il y a des spawn en jeu
        bool haveSpawnInProgress();

        bool haveBossInProgress();

        void spawn(std::tr1::shared_ptr<Enemy> enemy);

        static void kill();
        static Population* getInstance();
        void setPlayer(std::tr1::shared_ptr<Player> externPlayer, std::tr1::shared_ptr<Player> externPlayer2);

        void freeze();
        void unfreeze();
        bool isFreezed();

        void reset();

        int getKilledEnemies();
        unsigned short getCombo();

        void killThemAll();

    protected:
        //Liste des ennemis
        std::list<std::tr1::shared_ptr<Enemy> > m_enemies;

        //Liste des ennemis morts
        std::list<std::tr1::shared_ptr<Enemy> > m_deadEnemies;

        std::tr1::shared_ptr<Player> player;
        std::tr1::shared_ptr<Player> player2;

        std::tr1::shared_ptr<Boss> currentBoss;
        bool bossSpawned;

    private:
        //Constructeur privé pour singleton
        Population();

        Timer timerCombo;

        //Destructeur
        virtual ~Population();

        static Population* _singleton;

        bool freezed;

        short m_coefSpeed;
        int killedEnemies;
        unsigned short combo, maxCombo;
        short const killRate;

        Timer timerFreeze;

};


#endif // POPULATION_H_INCLUDED
