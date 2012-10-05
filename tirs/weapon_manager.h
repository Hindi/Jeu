#ifndef WEAPON_MANAGER_H_INCLUDED
#define WEAPON_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../player.h"

class Weapon_manager
{
    public:
        Weapon_manager();

        //Destructeur
        ~Weapon_manager();

        //Met à jour l'état des armes
        void manage();

    private:
        //Score limite pour activer les armes
        int secondaryScore, missileScore, thirdScore;
};

#endif // WEAPON_MANAGER_H_INCLUDED
