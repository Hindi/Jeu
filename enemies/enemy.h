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
        sf::Sprite* getSprite();

        //Accesseur sur le rectangle occup� par le sprite
         sf::IntRect getBoundingBox();

        //Inflige des dommages � l'ennemi
         void recieveDamages(int dmg);

        //Accesseur sur le score donn� par l'ennemis au joueur quand il touche
         short getScoreHit() const;
        //Accesseur sur le score donn� au joueur quand l'ennemi meurt
         unsigned short getScoreExplosion() const;

        //D�fini si l'ennemi est mort ou non
         bool isDead();

        // Aller retour horizontal sur valeur indiqu� (commence de gauche � droite)
         void roundTrip();

        //D�placements
         void moveLeft();
         void moveUp();
         void moveDown();
         void moveRight();
         void dontMove();
         void move();

        //Dessin de l'ennemi
         void draw();

        //Accesseur sur la position de l'ennemis sur un axe
         int getPositionAxis(int axis);

        //Accesseur sur la position de l'ennemi
         sf::Vector2f getPosition();
         void setPosition(int axis, int value);

        //Accesseur sur l'animation de l'ennemi (anim explosion dans Unit)
         Animated *getAnimationExplosion();
         Animated *getAnimation();

        //Diff�rents types de tirs
         void fireFocus();//Avec vis�e
         void fireCircle();//en cercle

        //Accesseur sur les projectiles en cours
         std::list<Projectile*>* getProjectiles();


        //D�fini si l'ennemi peut tirer ou non
         bool canFire();

        //Accesseur sur le type de tir
         char* getType();

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
        unsigned short const m_scoreExplosion;
        short const m_scoreHit, projectileSpeed, m_coefSpeed, m_fireRate;
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
        short  m_moveValue;

        //Permet de spawn des ennemis
        bool m_spawner;

        //Valeur li�es au timer pour le spawn
        float lastSpawn;
        short const m_spawnRate;
};


#endif // ENEMY_H_INCLUDED
