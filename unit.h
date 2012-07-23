#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "animation.h"
#include "Animated.hpp"
#include "projectile_manager.h"

//class mère des unités de jeu (player, enemy)

class Unit
{
    public:
        Unit(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, Projectile_manager &projectile_manager);
        virtual ~Unit();
        virtual int getLife();
        virtual void recieveDamages(int dmg);
        virtual bool isDead();
        virtual void drawExplosion();
        virtual int getExploWidth() const;
        virtual int getExploHeight() const;
        virtual sf::Vector2f getSpeed();
        virtual int getCoefSpeed() const;

    protected:
        Anim m_animExplosion;
        Animated *m_animatedExplosion;

        const sf::Vector2f m_scale;
        int const EXPLOS_WIDTH, EXPLOS_HEIGHT;
        sf::RenderWindow &m_app;
        sf::Vector2f m_position;
        sf::Sprite sprite;
        sf::Image *imageExplosion;

        int m_life;
        int m_xSpeed, m_ySpeed; // Vitesses sur chaque axe
        int const coefSpeed;
        int currentFrameX, currentFrameY;
        float x,y;
        Projectile_manager &m_projectile_manager;
};

#endif // UNIT_H_INCLUDED
