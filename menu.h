#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "image_manager.h"
#include "const.h"
#include <sstream>

class Menu
{
    public:
        Menu();
        //Destructeur
        ~Menu();

        //Menu de démarrage
        void drawMainMenu(int select, int score);

        void drawEndLevel(int select);

        //menu de pause
        void drawPauseMenu(int select);

        void setLevel(short nextLevel);

        short getLevel();

    protected:
        short levelMax;
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
        sf::Image *imageSuivant;
        sf::Image *imageSuivantFade;
        sf::Image *imageRecommencer;
        sf::Image *imageRecommencerFade;
        sf::Image *imageEndLevel;
        //sf::Image *imageContinuer;
        //sf::Image *imageFadeContinuer;

        //Les sprites de tous les menus
        sf::Sprite spritePlay;
        sf::Sprite spriteCredit;
        sf::Sprite spriteHow;
        sf::Sprite spritePause;
        sf::Sprite spriteReprendre;
        sf::Sprite spriteArreter;
        sf::Vector2f position;
        sf::Vector2f m_scale;
        sf::Sprite spriteSuivant;
        sf::Sprite spriteRecommencer;
        sf::Sprite spriteEndLevel;

        short currentLevel;
};

#endif // MENU_H_INCLUDED
