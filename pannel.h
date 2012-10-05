#ifndef PANNEL_H_INCLUDED
#define PANNEL_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "player.h"
#import "const.h"
#include "image_manager.h"

class Pannel
{
    public:
        Pannel(const std::string &filepath, sf::Vector2f position, Player &player);

        //Destructeur
        virtual ~Pannel();

        //Accesseur sur le sprite du pannel
        sf::Sprite* getSprite();

        //Mettent à jour le pannel
        void checkPannel();
        void drawLife();
        void drawScore();

    protected:
        //L'image sur le pannel
        sf::Image *imagePannel;

        //Le sprite du pannel
        sf::Sprite sprite;

        //Les images des icones de vie
        sf::Image *imageLife;
        sf::Image *imageLifeFade;

        //LEs sprites des icones de vie
        sf::Sprite spriteLife1;
        sf::Sprite spriteLife2;
        sf::Sprite spriteLife3;

        //Position du pannel
        sf::Vector2f m_position;

        //Echelle d'affichage
        const sf::Vector2f m_scale;

        //Variable du joueur
        Player &m_player;
};

#endif // PANNEL_H_INCLUDED
