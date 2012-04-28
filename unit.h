#ifndef UNIT_H_INCLUDED
#define UNIT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

//class mère des unités de jeu (player, enemy)

class Unit
{
    public:
        Unit(int life, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::RenderWindow &app, sf::IntRect subRect);
        virtual ~Unit();
        virtual int getLife();
        virtual void recieveDamages(int dmg);
        virtual void moveLeft();
        virtual void moveUp();
        virtual void moveDown();
        virtual void moveRight();
        virtual bool isDead();

    protected:
        const sf::Vector2f m_scale;
        sf::RenderWindow &m_app;
        sf::Image *image;
        sf::Vector2f m_position;
        sf::Sprite sprite;
        sf::IntRect m_subRect;
        int m_life;
        int m_xSpeed, m_ySpeed; // Vitesses sur chaque axe
        int const coefSpeed;
};

#endif // UNIT_H_INCLUDED
