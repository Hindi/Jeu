#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "population.h"
#include "timer.h"
#include "enemies/enemy.h"
#include "image_manager.h"
#include "player.h"
#include "population.h"
#include "tirs/projectile_manager.h"

class Script:public sf::Thread
{
    public:
        Script( short const id, std::string msg, image_manager &imageManager, Player &player);
        void niveau1();
        void niveau2();

    private:
        // Run() est une fonctione virtuelle de sf::Thread
        void Run();

        short const id;
        std::string msg;
        image_manager &m_imageManager;
        Player &m_player;
        Timer timer;
};

#endif // SCRIPT_H_INCLUDED
