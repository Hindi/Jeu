#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "player.h"
#include "enemy.h"
#include "collision.h"
#include "population.h"
#include "pannel.h"
#include <list>

class Jeu
{
    public:
        Jeu(sf::RenderWindow &app, int const SCREEN_WIDTH, int const SCREEN_HEIGHT);
        ~Jeu();
        void start();
        void pause();

    protected:
        sf::RenderWindow &m_app;
        int const m_SCREEN_WIDTH, m_SCREEN_HEIGHT;
};

#endif // JEU_H_INCLUDED
