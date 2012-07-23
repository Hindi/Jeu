#include "weapon_manager.h"

using namespace std;
using namespace sf;


Weapon_manager::Weapon_manager(Player &player): secondaryScore(20), missileScore(50),thirdScore(30), m_player(player)
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
