#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
    public:
        Menu(sf::RenderWindow &app);
        ~Menu();
        void drawMainMenu(int select);
        void drawPauseMenu(int select);

    protected:
        sf::RenderWindow &m_app;

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
