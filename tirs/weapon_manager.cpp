#include "weapon_manager.h"

using namespace std;
using namespace sf;

Weapon_manager* Weapon_manager::_singleton = NULL;

Weapon_manager::Weapon_manager():
            secondaryScore(1000),
            missileScore(10000),
            thirdScore(100000)
{
}

Weapon_manager::~Weapon_manager()
{
    this->reset();
}

void Weapon_manager::manage()
{
    if(player0->getScore() > missileScore)
    {
        player0->setMissile(true);
    }
    if(player0->getScore() > secondaryScore)
    {
        player0->setSecondary(true);
    }
    if(player0->getScore() > thirdScore)
    {
        player0->setThird(true);
    }
    if(player1->getScore() > missileScore)
    {
        player1->setMissile(true);
    }
    if(player1->getScore() > secondaryScore)
    {
        player1->setSecondary(true);
    }
    if(player1->getScore() > thirdScore)
    {
        player1->setThird(true);
    }
}


void Weapon_manager::setParams(std::tr1::shared_ptr<Player> externPlayer0, std::tr1::shared_ptr<Player> externPlayer1)
{
    player0 = externPlayer0;
    player1 = externPlayer1;
}

void Weapon_manager::kill()
{
    if(NULL != _singleton)
      {
         delete _singleton;
        _singleton = NULL;
      }
}

Weapon_manager* Weapon_manager::getInstance()
{
    if (NULL == _singleton)
      {
        std::cout << "weapon manager : creating singleton." << std::endl;
        _singleton =  new Weapon_manager;
      }

    return _singleton;
}

void Weapon_manager::reset()
{

}
