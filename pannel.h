#ifndef PANNEL_H_INCLUDED
#define PANNEL_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "player.h"

class Pannel
{
    public:
        Pannel(sf::RenderWindow &app, const std::string &filepath, sf::Vector2f position, Player &player);
        virtual ~Pannel();
        sf::Sprite* getSprite();
        void checkPannel();
        void drawLife();
        void drawScore();

    protected:
        sf::RenderWindow &m_app;
        sf::Image *imagePannel;
        sf::Image *imageLife;
        sf::Image *imageLifeFade;
        sf::Sprite spriteLife1;
        sf::Sprite spriteLife2;
        sf::Sprite spriteLife3;
        sf::Vector2f m_position;
        sf::Sprite sprite;
        const sf::Vector2f m_scale;
        Player &m_player;
};

#endif // PANNEL_H_INCLUDED
