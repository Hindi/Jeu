#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "animation.h"

//class mère des unités de jeu (player, enemy)

class Unit
{
    public:
        Unit(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app);
        virtual ~Unit();
        virtual int getLife();
        virtual void recieveDamages(int dmg);
        virtual bool isDead();

    protected:
        Animation *animation;
        const sf::Vector2f m_scale;
        sf::RenderWindow &m_app;
        sf::Image *image;
        sf::Vector2f m_position;
        sf::Sprite sprite;
        int m_life;
        int m_xSpeed, m_ySpeed; // Vitesses sur chaque axe
        int const coefSpeed;
        int currentFrameX, currentFrameY;
        float x,y;
};

#endif // UNIT_H_INCLUDED
