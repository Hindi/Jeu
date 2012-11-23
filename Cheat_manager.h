#ifndef CHEAT_MANAGER_H
#define CHEAT_MANAGER_H
#include "const.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "timer.h"


class Cheat_manager
{
    public:
        Cheat_manager();
        virtual ~Cheat_manager();
        void checkKonami();
        bool canPress();

    private:
        std::vector<char* > konamiCode;
        std::vector<char* > playerOneKonami;
        std::vector<char* > playerTwoKonami;
        bool sopalintMode;
        Timer timerPress;
};

#endif // CHEAT_MANAGER_H
