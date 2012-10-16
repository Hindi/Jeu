#ifndef WEAPON_MANAGER_H_INCLUDED
#define WEAPON_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../player.h"
#include <tr1/memory>

class Weapon_manager
{
    public:

        //Met à jour l'état des armes
        void manage();

        void setParams(std::tr1::shared_ptr<Player> externPlayer);

        static void kill();
        static Weapon_manager* getInstance();

    private:
        //Score limite pour activer les armes
        int secondaryScore, missileScore, thirdScore;

        std::tr1::shared_ptr<Player> player;

        Weapon_manager();

        //Destructeur
        ~Weapon_manager();

        static Weapon_manager* _singleton;
};

#endif // WEAPON_MANAGER_H_INCLUDED
