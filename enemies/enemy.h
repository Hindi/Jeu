#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "../player.h"
#include "../timer.h"
#include "../unit.h"
#include "../tirs/projectile.h"
#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "math.h"
#include "../tirs/projectile_manager.h"
#include "../const.h"

//Permet de créer le type enemy : ils sont ensuite créé et stocké dans population.

class Enemy : public Unit
{
    public:
        Enemy(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, const char* const type, const std::string &moveMethod, int moveValue,
              const int coefSpeed, const int firerate,bool spawner, std::tr1::shared_ptr<Player> externPlayer, std::tr1::shared_ptr<Player> externPlayer2, bool allowTeleport);

        //Destructeur
        virtual ~Enemy();

        //Accesseur sur le sprite
        sf::Sprite* getSprite();

        //Accesseur sur le rectangle occupé par le sprite
         virtual sf::IntRect getBoundingBox();
         virtual sf::IntRect getWeakBox();

        //Inflige des dommages à l'ennemi
         void recieveDamages(int dmg);

        //Accesseur sur le score donné par l'ennemis au joueur quand il touche
         short getScoreHit() const;
        //Accesseur sur le score donné au joueur quand l'ennemi meurt
         unsigned short getScoreExplosion() const;

        //Défini si l'ennemi est mort ou non
         bool isDead();

        // Aller retour horizontal sur valeur indiqué (commence de gauche à droite)
         void roundTrip();

        //Déplacements
         void moveLeft();
         void moveUp();
         void moveDown();
         void moveRight();
         void dontMove();
         virtual void move();
         void spawnMove();
         virtual void follow();

        //Dessin de l'ennemi
         virtual void draw();

        //Accesseur sur la position de l'ennemis sur un axe
         int getPositionAxis(int axis);

        //Accesseur sur la position de l'ennemi
         sf::Vector2f getPosition();
         void setPosition(int axis, int value);
         void setPosition(sf::Vector2f position);

        //Accesseur sur l'animation de l'ennemi (anim explosion dans Unit)
         Animated *getAnimationExplosion();
         Animated *getAnimation();

        //Différents types de tirs
         void fireFocus();//Avec visée
         void fireCircle();//en cercle
         void VFire();//Tir en V à l'avant
         virtual void fire();
         void fireSpawner();

        //Accesseur sur les projectiles en cours
         std::list<std::tr1::shared_ptr<Projectile> >* getProjectiles();


        //Défini si l'ennemi peut tirer ou non
         bool canFire();

        //Accesseur sur le type de tir
         const char* getType();

        //Timer pour les tirs
         void startTimer();
         void pauseTimer();

        //Retourne true si l'ennemis est capable de spawn des mobs
        bool isSpawner();

        //Retourne la valeur du timer spawn
        float getSpawnTime();

        //Retourne le moment du dernier spawn
        float getLastSpawnTime();

        //Modifie la valeur du dernier spawn
        void upDateLastSpawnTime();

        //Retourn le spawn rate
        short getSpawnRate() const;

        void freeze();
        void unfreeze();

        sf::Vector2f getSize();

        void reset();


        virtual bool canTeleport();
        virtual void setTeleporting(bool state);
        bool readyToTeleport();
        virtual void teleport();

    protected:
        std::tr1::shared_ptr<Player> player;
        std::tr1::shared_ptr<Player> player2;

        //listes des projectils et de leurs vitesse (en cas de visée)
        std::list<std::tr1::shared_ptr<Projectile> > m_projectiles;
        std::list<sf::Vector2f> m_vitesses;

        //Direction de déplacememnt pour certains mouvements particuliers
        std::string direction;

        sf::Image *image;

        //Temps au dernier tir
        float lastShot;

        //Timers pour les tirs et les déplacememnts
        Timer timer, timerMove, timerSpawn;

        //Constantes de score, vitesse et fréquence de tir
        unsigned short const m_scoreExplosion;
        short const m_scoreHit, projectileSpeed,  m_fireRate;
        //Sauvegarde du timer de déplacement
        float savedTimerMove;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        //Position du joueur (en cas de visée)
        sf::Vector2f playerPosition;

        //type de tir
        const char* const m_type;

        //type de déplacement
        const std::string m_moveMethod;

        //Etat du déplacement
        short  m_moveValue, m_coefSpeed;

        //Permet de spawn des ennemis
        bool m_spawner;

        //Valeur liées au timer pour le spawn
        float lastSpawn;
        short const m_spawnRate;

        unsigned short m_angleMove;


        bool teleporting, allowTeleport;
        int teleportFrame;
        Timer teleportTimer;
};


#endif // ENEMY_H_INCLUDED
