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

//Permet de cr�er le type enemy : ils sont ensuite cr�� et stock� dans population.

class Enemy : public Unit
{
    public:
        Enemy(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate, sf::RenderWindow &app, Player &player, image_manager &imageManager, Projectile_manager &projectile_manager, bool spawner);

        //Destructeur
        ~Enemy();

        //Accesseur sur le sprite
        virtual sf::Sprite* getSprite();

        //Accesseur sur le rectangle occup� par le sprite
        virtual sf::IntRect getBoundingBox();

        //Inflige des dommages � l'ennemi
        virtual void recieveDamages(int dmg);

        //Accesseur sur le score donn� par l'ennemis au joueur quand il touche
        virtual int getScoreHit();
        //Accesseur sur le score donn� au joueur quand l'ennemi meurt
        virtual int getScoreExplosion();

        //D�fini si l'ennemi est mort ou non
        virtual bool isDead();

        // Aller retour horizontal sur valeur indiqu� (commence de gauche � droite)
        virtual void roundTrip();

        //D�placements
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

        //Diff�rents types de tirs
        virtual void fireFocus();//Avec vis�e
        virtual void fireCircle();//en cercle

        //Accesseur sur les projectiles en cours
        virtual std::list<Projectile*>* getProjectiles();


        //D�fini si l'ennemi peut tirer ou non
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

        //listes des projectils et de leurs vitesse (en cas de vis�e)
        std::list<Projectile*> m_projectiles;
        std::list<sf::Vector2f> m_vitesses;

        //Direction de d�placememnt pour certains mouvements particuliers
        char* direction;

        Projectile *projectile;
        sf::Image *image;

        //Temps au dernier tir
        float lastShot;

        //Timers pour les tirs et les d�placememnts
        Timer timer, timerMove, timerSpawn;

        //Constantes de score, vitesse et fr�quence de tir
        int const m_scoreHit, m_scoreExplosion, projectileSpeed, m_coefSpeed, m_fireRate;

        //Sauvegarde du timer de d�placement
        float savedTimerMove;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        //Manager d'image
        image_manager &m_imageManager;

        //Position du joueur (en cas de vis�e)
        sf::Vector2f playerPosition;

        //type de tir
        char* m_type;

        //type de d�placement
        char* m_moveMethod;

        //Etat du d�placement
        int  m_moveValue;

        //Permet de spawn des ennemis
        bool m_spawner;

        //Valeur li�es au timer pour le spawn
        int lastSpawn;
        const int m_spawnRate;
};


#endif // ENEMY_H_INCLUDED
