#ifndef PANNEL_H_INCLUDED
#define PANNEL_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "player.h"
#import "const.h"
#include "image_manager.h"
#include "population.h"

class Pannel
{
    public:
        Pannel(const std::string &filepath, sf::Vector2f position, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);

        //Destructeur
        virtual ~Pannel();

        //Accesseur sur le sprite du pannel
        sf::Sprite* getSprite();

        //Mettent à jour le pannel
        void checkPannel();
        void drawLife();
        void drawScore();
        void drawEnemyStats();
        void drawArmor();

    protected:
        //L'image sur le pannel
        sf::Image *imagePannel;
        sf::Image *imageTopPannel;
        sf::Image *imageTopPannel2;

        //Le sprite du pannel
        sf::Sprite sprite;
        sf::Sprite topPannel;
        sf::Sprite topPannel2;

        //Les images des icones de vie
        sf::Image *imageLife;
        sf::Image *imageLifeFade;

        //Les images des icones d'armure
        sf::Image *imageArmor;
        sf::Image *imageArmorFade;

        //LEs sprites des icones de vie
        sf::Sprite spriteLife1;
        sf::Sprite spriteLife2;
        sf::Sprite spriteLife3;
        sf::Sprite spriteLife21;
        sf::Sprite spriteLife22;
        sf::Sprite spriteLife23;

        //LEs sprites des icones de l'armure
        sf::Sprite spriteArmor1;
        sf::Sprite spriteArmor2;
        sf::Sprite spriteArmor3;
        sf::Sprite spriteArmor21;
        sf::Sprite spriteArmor22;
        sf::Sprite spriteArmor23;


        //Position du pannel
        sf::Vector2f m_position;

        //Echelle d'affichage
        const sf::Vector2f m_scale;

        //Variable du joueur
        std::tr1::shared_ptr<Player> m_player, m_player2;
};

#endif // PANNEL_H_INCLUDED
