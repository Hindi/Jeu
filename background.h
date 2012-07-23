#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "image_manager.h"

class Background
{
    public:
        Background(sf::RenderWindow &app, int speed, int SCREEN_WIDTH, int SCREEN_HEIGHT, image_manager &imageManager);
        virtual ~Background();
        void manage();
        void init();

    protected:
        int LIST_SIZE;
        sf::Image *imageStar, *imagePlanet;
        sf::Sprite spriteStar, spritePlanet;
        sf::RenderWindow &m_app;
        std::vector<sf::Sprite> listStar;
        int m_speed;
        int const m_width, m_height;
};

#endif // BACKGROUND_H_INCLUDED
