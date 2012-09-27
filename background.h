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

        //Destructeur
        virtual ~Background();

        //Met à jour
        void manage();

        //Créé les sprite et les positionne
        void init();

    protected:

        //Nombre d'étoiles
        short LIST_SIZE;

        //Images étoiles et planète
        sf::Image *imageStar, *imagePlanet;

        //Sprites étoiles et planètes
        sf::Sprite spriteStar, spritePlanet;

        //Fenêtre
        sf::RenderWindow &m_app;

        //Liste d'étoiles
        std::vector<sf::Sprite> listStar;

        //Vitesse de déplacement des étoiles
        short m_speed;

        //Taille de la fenêtre
        int const m_width, m_height;
};

#endif // BACKGROUND_H_INCLUDED
