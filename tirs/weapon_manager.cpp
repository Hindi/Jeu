#include "weapon_manager.h"

using namespace std;
using namespace sf;


Weapon_manager::Weapon_manager():
            secondaryScore(1000),
            missileScore(10000),
            thirdScore(500000)
{

}

Weapon_manager::~Weapon_manager()
{

}

void Weapon_manager::manage()
{
    if(player->getScore() > missileScore)
    {
        player->setMissile(true);
    }
    if(player->getScore() > secondaryScore)
    {
        player->setSecondary(true);
    }
    if(player->getScore() > thirdScore)
    {
        player->setThird(true);
    }
}


void Weapon_manager::setParams(Player *externPlayer)
{
    player = externPlayer;
}
