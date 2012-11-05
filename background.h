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
        Background(int speed, int SCREEN_WIDTH, int SCREEN_HEIGHT, sf::RenderWindow &app);

        //Destructeur
        virtual ~Background();

        //Met � jour
        void manage();

        //Cr�� les sprite et les positionne
        void init();

    protected:
        sf::RenderWindow &app;

        //Nombre d'�toiles
        short LIST_SIZE;

        //Images �toiles et plan�te
        sf::Image *imageStar, *imageStar2,*imagePlanet, *imagePlanet2;

        //Sprites �toiles et plan�tes
        sf::Sprite spriteStar, spritePlanet, spritePlanet2;

        //Liste d'�toiles
        std::vector<sf::Sprite> listStar;

        //Vitesse de d�placement des �toiles
        short m_speed;

        //Taille de la fen�tre
        const int m_width, m_height;
};

#endif // BACKGROUND_H_INCLUDED
