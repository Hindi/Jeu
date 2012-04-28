#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include "projectile.h"
#include "unit.h"
#include "timer.h"


//Tout ce qui concerne le joueur

class Player : public Unit
{
    public:
        Player(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, sf::IntRect subRect);
        ~Player();
        sf::Sprite* getSprite();
        int getLives();
        sf::IntRect GetBoundingBox() const;
        void fire();
        bool HaveProjectilesInProgress();
        std::list<Projectile*>* getProjectiles();
        void moveProjectile();
        void drawProjectile();
        void addScore(int score);
        double getScore();
        void loseLive();
        bool getLostlife();
        void resetLostLife();
        void refreshPosition();

    protected:
        std::list<Projectile*> m_projectiles;
        Projectile *projectile;
        int m_lives; //Vies restantes
        int const max_lives; //Nombre de vie non dépassable
        float const fireRate; //delta en secondes entre chaque tir
        float lastShot;
        Timer timer;
        double m_score;
        bool lostLife;
};

bool canFire(float lastShot, Timer &timer, float const fireRate);

#endif // PLAYER_H_INCLUDED
