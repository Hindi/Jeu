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

//Permet de créer le type enemy : ils sont ensuite créé et stocké dans population.

class Enemy : public Unit
{
    public:
        Enemy(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate, sf::RenderWindow &app, Player &player, image_manager &imageManager, Projectile_manager &projectile_manager, bool spawner);

        //Destructeur
        ~Enemy();

        //Accesseur sur le sprite
        virtual sf::Sprite* getSprite();

        //Accesseur sur le rectangle occupé par le sprite
        virtual sf::IntRect getBoundingBox();

        //Inflige des dommages à l'ennemi
        virtual void recieveDamages(int dmg);

        //Accesseur sur le score donné par l'ennemis au joueur quand il touche
        virtual int getScoreHit();
        //Accesseur sur le score donné au joueur quand l'ennemi meurt
        virtual int getScoreExplosion();

        //Défini si l'ennemi est mort ou non
        virtual bool isDead();

        // Aller retour horizontal sur valeur indiqué (commence de gauche à droite)
        virtual void roundTrip();

        //Déplacements
        virtual void moveLeft();
        virtual void moveUp();
        virtual void moveDown();
        virtual void moveRight();
        virtual void dontMove();
        virtual void move();

        //Dessin de l'ennemi
        virtual void draw();

        //Accesseur sur la position de l'ennemis sur un axe
        virtual int getPositionAxis(int axis);

        //Accesseur sur la position de l'ennemi
        virtual sf::Vector2f getPosition();
        virtual void setPosition(int axis, int value);

        //Accesseur sur l'animation de l'ennemi (anim explosion dans Unit)
        virtual Animated *getAnimationExplosion();
        virtual Animated *getAnimation();

        //Différents types de tirs
        virtual void fireFocus();//Avec visée
        virtual void fireCircle();//en cercle

        //Accesseur sur les projectiles en cours
        virtual std::list<Projectile*>* getProjectiles();


        //Défini si l'ennemi peut tirer ou non
        virtual bool canFire();

        //Accesseur sur le type de tir
        virtual char* getType();

        //Timer pour les tirs
        virtual void startTimer();
        virtual void pauseTimer();

        //Retourne true si l'ennemis est capable de spawn des mobs
        bool isSpawner();

        //Retourne la valeur du timer spawn
        float getSpawnTime();

        //Retourne le moment du dernier spawn
        float getLastSpawnTime();

        //Modifie la valeur du dernier spawn
        void upDateLastSpawnTime();

        //Retourn le spawn rate
        int getSpawnRate();


    protected:
        //Joueur
        Player &m_player;

        //listes des projectils et de leurs vitesse (en cas de visée)
        std::list<Projectile*> m_projectiles;
        std::list<sf::Vector2f> m_vitesses;

        //Direction de déplacememnt pour certains mouvements particuliers
        char* direction;

        Projectile *projectile;
        sf::Image *image;

        //Temps au dernier tir
        float lastShot;

        //Timers pour les tirs et les déplacememnts
        Timer timer, timerMove, timerSpawn;

        //Constantes de score, vitesse et fréquence de tir
        int const m_scoreHit, m_scoreExplosion, projectileSpeed, m_coefSpeed, m_fireRate;

        //Sauvegarde du timer de déplacement
        float savedTimerMove;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        //Manager d'image
        image_manager &m_imageManager;

        //Position du joueur (en cas de visée)
        sf::Vector2f playerPosition;

        //type de tir
        char* m_type;

        //type de déplacement
        char* m_moveMethod;

        //Etat du déplacement
        int  m_moveValue;

        //Permet de spawn des ennemis
        bool m_spawner;

        //Valeur liées au timer pour le spawn
        int lastSpawn;
        const int m_spawnRate;
};


#endif // ENEMY_H_INCLUDED
