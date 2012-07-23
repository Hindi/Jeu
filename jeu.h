#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <list>
#include "player.h"
#include "enemy.h"
#include "collision.h"
#include "population.h"
#include "pannel.h"
#include "timer.h"
#include "menu.h"
#include "script.h"
#include "background.h"
#include "image_manager.h"
#include "projectile_manager.h"
#include "guard.h"
#include "tirs/missile_manager.h"
#include "weapon_manager.h"
#include "drop_manager.h"


class Jeu
{
    public:
        Jeu(sf::RenderWindow &app, int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu);
        ~Jeu();
        void start();
        void pause(Population &population, sf::Event event, Pannel &pannel, Player &player);
        void func();

    protected:
        sf::RenderWindow &m_app;
        int const m_SCREEN_WIDTH, m_SCREEN_HEIGHT;
        Menu &m_menu;
        bool m_quit;
};

void func();

#endif // JEU_H_INCLUDED
