#ifndef CHEAT_MANAGER_H
#define CHEAT_MANAGER_H
#include "const.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "timer.h"


class Cheat_manager
{
    public:
        virtual ~Cheat_manager();
        void checkKonami();
        void checkVector(std::deque<char* > konami);
        bool getSopalintMode();

        static Cheat_manager* getInstance();

    private:
        std::deque<char* > konamiCode;
        std::deque<char* > playerOneKonami;
        std::deque<char* > playerTwoKonami;
        bool sopalintMode;
        Timer timerPress;
        Timer timerSopalint;


        Cheat_manager();
        static Cheat_manager* _singleton;
};

#endif // CHEAT_MANAGER_H
