#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "image_manager.h"

class Menu
{
    public:
        Menu(sf::RenderWindow &app, image_manager imageManager);
        //Destructeur
        ~Menu();

        //Menu de démarrage
        void drawMainMenu(int select);

        //menu de pause
        void drawPauseMenu(int select);

    protected:
        //La fenêtre
        sf::RenderWindow &m_app;
        //Manager d'images
        image_manager &m_imageManager;

        //Les imagesde tous les menus
        sf::Image *imagePlay;
        sf::Image *imageCredit;
        sf::Image *imageHow;
        sf::Image *imageFadePlay;
        sf::Image *imageFadeCredit;
        sf::Image *imageFadeHow;
        sf::Image *imagePause;
        sf::Image *imageReprendre;
        sf::Image *imageArreter;
        sf::Image *imageFadePause;
        sf::Image *imageFadeReprendre;
        sf::Image *imageFadeArreter;

        //Les sprites de tous les menus
        sf::Sprite spritePlay;
        sf::Sprite spriteCredit;
        sf::Sprite spriteHow;
        sf::Sprite spritePause;
        sf::Sprite spriteReprendre;
        sf::Sprite spriteArreter;
        sf::Vector2f position;
        sf::Vector2f m_scale;
};

#endif // MENU_H_INCLUDED
