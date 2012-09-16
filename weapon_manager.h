#ifndef WEAPON_MANAGER_H_INCLUDED
#define WEAPON_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "player.h"

class Weapon_manager
{
    public:
        Weapon_manager(Player &player);
        ~Weapon_manager();
        void manage();

    private:
        int secondaryScore, missileScore, thirdScore;
        Player &m_player;
};

#endif // WEAPON_MANAGER_H_INCLUDED
