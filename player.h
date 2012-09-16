#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "projectile.h"
#include "unit.h"
#include "timer.h"
#include "animation.h"
#include "image_manager.h"
#include "projectile_manager.h"
#include "tirs/missile.h"

class Player : public Unit
{
    public:
        Player(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, image_manager &imagemManager, Projectile_manager &projectile_manager);
        ~Player();
        sf::Sprite* getSprite();
        int getLives();
        sf::IntRect GetBoundingBox();
        void fire();
        std::list<Projectile*>* getProjectiles();
        void moveProjectile();
        void drawProjectile();
        void addScore(int score);
        double getScore();
        void loseLive();
        bool getLostlife();
        void resetLostLife();
        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void dontMove();
        void draw();
        int getPosition(int axis);
        void setPosition(int axis, int value);
        int getDamages();
        bool getMissile();
        bool getSecondary();
        void setMissile(bool mode);
        void setSecondary(bool mode);
        void setThird(bool mode);

    protected:
        std::list<Projectile*> m_projectiles;
        sf::Vector2f m_speed;
        Projectile *projectile, *projectileDroite, *projectileGauche, *projectileExtremeDroite, *projectileExtremeGauche;
        Missile *missile;
        int m_damages, m_lives; //Vies restantes
        int const max_lives, m_frameWidth, m_frameHeight, m_coefSpeed;
        float const fireRate; //delta en secondes entre chaque tir
        float lastShot;
        Timer timer;
        double m_score;
        bool lostLife, missiles, secondary, third;
        Animated *m_animated;
        Anim m_anim, goRight, goLeft;
        sf::Image *image;
        image_manager &m_imageManager;

};

bool canFire(float lastShot, Timer &timer, float const fireRate);

#endif // PLAYER_H_INCLUDED
