#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <list>
#include "player.h"
#include "enemies/enemy.h"
#include "collision.h"
#include "population.h"
#include "pannel.h"
#include "timer.h"
#include "menu.h"
#include "script.h"
#include "background.h"
#include "image_manager.h"
#include "tirs/projectile_manager.h"
#include "guard.h"
#include "tirs/missile_manager.h"
#include "weapon_manager.h"
#include "drop_manager.h"


class Jeu
{
    public:
        Jeu(sf::RenderWindow &app, int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu, image_manager imageManager);

        //Destructeur
        ~Jeu();

        //Démarre la partie
        void start();

        //Met en pause la partie
        void pause(Population &population, sf::Event event, Pannel &pannel, Player &player);

    protected:
        //La fenêtre
        sf::RenderWindow &m_app;

        //Manager d'images
        image_manager &m_imageManager;

        //Taille de la fenêtre
        int const m_SCREEN_WIDTH, m_SCREEN_HEIGHT;

        //Objet menu pour lancer la partie et mettre en pause
        Menu &m_menu;

        //Pour quitter la partie en cours
        bool m_quit;
};

#endif // JEU_H_INCLUDED
