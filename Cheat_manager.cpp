#include "Cheat_manager.h"

using namespace sf;

Cheat_manager *Cheat_manager::_singleton= NULL;

Cheat_manager::Cheat_manager()
{
    konamiCode.push_back("u");
    konamiCode.push_back("u");
    konamiCode.push_back("d");
    konamiCode.push_back("d");
    konamiCode.push_back("l");
    konamiCode.push_back("r");
    konamiCode.push_back("l");
    konamiCode.push_back("r");
    konamiCode.push_back("b");
    konamiCode.push_back("a");

    sopalintMode = false;

    timerPress.start();
    timerSopalint.start();
}

Cheat_manager::~Cheat_manager()
{
    konamiCode.clear();
    playerOneKonami.clear();
    playerTwoKonami.clear();
}

void Cheat_manager::checkKonami()
{
    Event Event;
    const Input & input = app.GetInput();
    if(timerPress.getTime() > 0.2 && !sopalintMode)
    {
        if((input.IsKeyDown(Key::Down)))
        {
            playerOneKonami.push_back("d");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::Up)))
        {
            playerOneKonami.push_back("u");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::Left)))
        {
            playerOneKonami.push_back("l");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::Right)))
        {
            playerOneKonami.push_back("r");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::B)))
        {
            playerOneKonami.push_back("b");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::A)))
        {
            playerOneKonami.push_back("a");
            timerPress.reinitialize();
        }

        if((input.IsKeyDown(Key::Z)))
        {
            playerTwoKonami.push_back("d");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::S)))
        {
            playerTwoKonami.push_back("u");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::Q)))
        {
            playerTwoKonami.push_back("l");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::D)))
        {
            playerTwoKonami.push_back("r");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::N)))
        {
            playerTwoKonami.push_back("b");
            timerPress.reinitialize();
        }
        if((input.IsKeyDown(Key::E)))
        {
            playerTwoKonami.push_back("a");
            timerPress.reinitialize();
        }
    }
    if(playerOneKonami.size() == 10)
    {
        int result(0);
        for(int i(0); i<10; i++)
        {
            if(strcmp(konamiCode[i], playerOneKonami[i]) == 0)
                result++;
        }
        if(result == 10 && !sopalintMode)
        {
            sopalintMode = true;
        }
    }

    if(sopalintMode && timerSopalint.getTime() > 10)
        sopalintMode = false;
}

bool Cheat_manager::getSopalintMode()
{
    return sopalintMode;
}

Cheat_manager* Cheat_manager::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "population : creating singleton." << std::endl;
        _singleton =  new Cheat_manager;
      }

    return _singleton;
  }
