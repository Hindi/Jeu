#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include "timer.h"
#include "unit.h"
#include "projectile.h"
#include "animation.h"

//Permet de créer le type enemy : ils sont ensuite créé et stocké dans population.

class Enemy : public Unit
{
    public:
        Enemy(int life, int score, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app);
        ~Enemy();
        sf::Sprite* getSprite();
        sf::IntRect getBoundingBox();
        std::list<Projectile*> fire();
        std::list<Projectile*> getProjectiles();
        void recieveDamages(int dmg);
        int getScore();
        bool isDead();
        void moveLeft();
        void moveUp();
        void moveDown();
        void moveRight();
        void draw();
        int getPosition(int axis);
        void setPosition(int axis, int value);

    protected:
        std::list<Projectile*> m_projectiles;
        static sf::Image image;
        float lastShot;
        Timer timer;
        int const m_score;
};

#endif // ENEMY_H_INCLUDED
