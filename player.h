#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "tirs/projectile.h"
#include "unit.h"
#include "timer.h"
#include "animation.h"
#include "tirs/missile.h"
#include "image_manager.h"
#include "tirs/projectile_manager.h"

class Player : public Unit
{
    public:
        Player(short id, int life, sf::Vector2f position);
        //Destructeur
        ~Player();

        //Accesseur sur le sprite du joueur
        sf::Sprite* getSprite();

        //Accesseur sur le nombre de vies
        short getLives();

        //accesseur sur le rectangle du sprite
        sf::IntRect GetBoundingBox();

        //Fait tirer le joueur
        void fire0();
        void fire1();

        //D�place les projectiles
        void moveProjectile();

        //Dessine les projectiles
        void drawProjectile();

        //Augmente le score du joueur
        void addScore(int score);

        //accesseur sur le score
        int getScore();

        //Fait perdre une vie
        void loseLive();

        //accesseur sur l'�tat du joueur (vient de perdre une vie ou non)
        bool getLostlife();

        //Remet le joueur dans l'�tat dans lequel ile st susceptible de perdre une vie
        void resetLostLife();

        //D�placements
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void dontMove();

        //Dessiner le joueur
        void draw();

        //accesseur sur la position
        int getPosition(int axis);
        sf::Vector2f getPosition();
        void setPosition(int axis, int value);

        //accesseur sur le nombre de dommages
        short getDamages() const;

        //accesseur sur les missiles du joueur
        bool getMissile();

        //accesseur sur l'arme secondaire
        bool getSecondary();

        //Setters
        void setMissile(bool mode);
        void setSecondary(bool mode);
        void setThird(bool mode);

        short getArmor();

        bool getPlayerKTA();
        void setPlayerKTA(bool state);

        void checkKTA();

        bool isDead();

    protected:
        //Vitesse du joueur
        sf::Vector2f m_speed;

        //Dommages inflig�s et nombre de vies
        short const m_damages;
        short m_lives;
        short m_armor;

        //Nombre max de vie du joueur, taille du sprite et coef de d�placememnt
        short const max_lives, m_coefSpeed;
        int const  m_frameWidth, m_frameHeight;

        //Temps entre deux tirs en secondes
        float const fireRate;

        //Moment du dernier tir
        float lastShot;

        //Timer sur les tirs
        Timer timer;
        Timer timerArmor;
        Timer timerKillThemAll;

        //Score courant du joueur
        long double m_score;

        //Etat invincible ou non du joueur, activations des diff�rentes armes
        bool lostLife, missiles, secondary, third;

        //Variables d'animation
        Animated *m_animated;

        //Contiennent les framesp our les diff�rents d�placements
        Anim m_anim, goRight, goLeft;

        //Animation r�acteur
        Animated *m_animatedReactor;

        //Contient les frames du r�acteur
        Anim m_animReactor;

        //L'image associ�e au sprite du vaisseau
        sf::Image *image;

        //Image du r�acteur
        sf::Image *imageReactor;

        bool killThemAll;

};

//Autorise ou non les tirs
bool canFire(float lastShot, Timer &timer, float const fireRate);

#endif // PLAYER_H_INCLUDED
