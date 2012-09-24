#include "weapon_manager.h"

using namespace std;
using namespace sf;


Weapon_manager::Weapon_manager(Player &player):
            secondaryScore(1000),
            missileScore(10000),
            thirdScore(500000),
            m_player(player)
{

}

Weapon_manager::~Weapon_manager()
{

}

void Weapon_manager::manage()
{
    if(m_player.getScore() > missileScore)
    {
        m_player.setMissile(true);
    }
    if(m_player.getScore() > secondaryScore)
    {
        m_player.setSecondary(true);
    }
    if(m_player.getScore() > thirdScore)
    {
        m_player.setThird(true);
    }
}
