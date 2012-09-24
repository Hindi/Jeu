#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "tirs/projectile.h"
#include "unit.h"
#include "timer.h"
#include "animation.h"
#include "image_manager.h"
#include "tirs/projectile_manager.h"
#include "tirs/missile.h"

class Player : public Unit
{
    public:
        Player(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, image_manager &imagemManager, Projectile_manager &projectile_manager);
        //Destructeur
        ~Player();

        //Accesseur sur le sprite du joueur
        sf::Sprite* getSprite();

        //Accesseur sur le nombre de vies
        int getLives();

        //accesseur sur le rectangle du sprite
        sf::IntRect GetBoundingBox();

        //Fait tirer le joueur
        void fire();

        //accesseur sur les projectiles du joueur
        std::list<Projectile*>* getProjectiles();

        //Déplace les projectiles
        void moveProjectile();

        //Dessine les projectiles
        void drawProjectile();

        //Augmente le score du joueur
        void addScore(int score);

        //accesseur sur le score
        double getScore();

        //Fait perdre une vie
        void loseLive();

        //accesseur sur l'état du joueur (vient de perdre une vie ou non)
        bool getLostlife();

        //Remet le joueur dans l'état dans lequel ile st susceptible de perdre une vie
        void resetLostLife();

        //Déplacements
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void dontMove();

        //Dessiner le joueur
        void draw();

        //accesseur sur la position
        int getPosition(int axis);
        void setPosition(int axis, int value);

        //accesseur sur le nombre de dommages
        int getDamages();

        //accesseur sur les missiles du joueur
        bool getMissile();

        //accesseur sur l'arme secondaire
        bool getSecondary();

        //Setters
        void setMissile(bool mode);
        void setSecondary(bool mode);
        void setThird(bool mode);

    protected:
        //Liste des projectiles du joueur
        std::list<Projectile*> m_projectiles;

        //Vitesse du joueur
        sf::Vector2f m_speed;

        //Tous les projectiles (main, et secondaires)
        Projectile *projectile, *projectileDroite, *projectileGauche, *projectileExtremeDroite, *projectileExtremeGauche;

        //Le missile
        Missile *missile;

        //Dommages infligés et nombre de vies
        int m_damages, m_lives;

        //Nombre max de vie du joueur, taille du sprite et coef de déplacememnt
        int const max_lives, m_frameWidth, m_frameHeight, m_coefSpeed;

        //Temps entre deux tirs en secondes
        float const fireRate;

        //Moment du dernier tir
        float lastShot;

        //Timer sur les tirs
        Timer timer;

        //Score courant du joueur
        double m_score;

        //Etat invincible ou non du joueur, activations des différentes armes
        bool lostLife, missiles, secondary, third;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim, goRight, goLeft;

        //L'image associée au sprite
        sf::Image *image;

        //Manager d'image
        image_manager &m_imageManager;

};

//Autorise ou non les tirs
bool canFire(float lastShot, Timer &timer, float const fireRate);

#endif // PLAYER_H_INCLUDED
