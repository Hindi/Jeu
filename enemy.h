#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED
#include <list>
#include <string>
#include <SFML/Graphics.hpp>
#include "player.h"
#include "timer.h"
#include "unit.h"
#include "projectile.h"
#include "animation.h"
#include "Animated.hpp"
#include "image_manager.h"
#include "math.h"
#include "projectile_manager.h"

//Permet de créer le type enemy : ils sont ensuite créé et stocké dans population.

class Enemy : public Unit
{
    public:
        Enemy(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate, sf::RenderWindow &app, Player &player, image_manager &imageManager, Projectile_manager &projectile_manager);
        ~Enemy();
        sf::Sprite* getSprite();
        sf::IntRect getBoundingBox();
        void recieveDamages(int dmg);
        int getScoreHit();
        int getScoreExplosion();
        bool isDead();
        void roundTrip(); // Aller retour horizontal sur valeur indiqué (commence de gauche à droite)
        void moveLeft();
        void moveUp();
        void moveDown();
        void moveRight();
        void dontMove();
        void move();
        void draw();
        int getPositionAxis(int axis);
        sf::Vector2f getPosition();
        void setPosition(int axis, int value);
        Animated *getAnimationExplosion();
        Animated *getAnimation();
        void fireFocus();
        void fireCircle();
        std::list<Projectile*>* getProjectiles();
        bool HaveProjectilesInProgress();
        void moveProjectile();
        void drawProjectile();
        bool canFire();
        char* getType();
        void startTimer();
        void pauseTimer();


    protected:
        Player &m_player;
        std::list<Projectile*> m_projectiles;
        std::list<sf::Vector2f> m_vitesses;
        char* direction;
        Projectile *projectile;
        sf::Image *image;
        float lastShot;
        Timer timer, timerMove;
        int const m_scoreHit, m_scoreExplosion, projectileSpeed, m_coefSpeed, m_fireRate;
        float savedTimerMove;
        Animated *m_animated;
        Anim m_anim;
        image_manager &m_imageManager;
        sf::Vector2f playerPosition;
        char* m_type;
        char* m_moveMethod;
        int  m_moveValue;
};


#endif // ENEMY_H_INCLUDED
