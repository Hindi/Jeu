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

        //Met à jour
        void manage();

        //Créé les sprite et les positionne
        void init();

    protected:
        sf::RenderWindow &app;

        //Nombre d'étoiles
        short LIST_SIZE;

        //Images étoiles et planète
        sf::Image *imageStar, *imageStar2,*imagePlanet, *imagePlanet2;

        //Sprites étoiles et planètes
        sf::Sprite spriteStar, spritePlanet, spritePlanet2;

        //Liste d'étoiles
        std::vector<sf::Sprite> listStar;

        //Vitesse de déplacement des étoiles
        short m_speed;

        //Taille de la fenêtre
        const int m_width, m_height;
};

#endif // BACKGROUND_H_INCLUDED
