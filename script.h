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
#include "const.h"

class Script:public sf::Thread
{
    public:
        Script( short const id);
        void niveau1();
        void niveau2();

        bool isFinished();

        short nextLevel();

        void setLaunchLevel(short launchLevel);


    private:
        // Run() est une fonctione virtuelle de sf::Thread
        void Run();

        short const id;
        Timer timer;

        bool finished;
        short currentLevel, m_launchLevel;
};

#endif // SCRIPT_H_INCLUDED
