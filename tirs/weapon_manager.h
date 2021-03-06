#ifndef WEAPON_MANAGER_H_INCLUDED
#define WEAPON_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../player.h"

class Weapon_manager
{
    public:

        //Met � jour l'�tat des armes
        void manage();

        void setParams(std::tr1::shared_ptr<Player> externPlayer0, std::tr1::shared_ptr<Player> externPlayer1);

        static void kill();
        static Weapon_manager* getInstance();
        //Destructeur
        ~Weapon_manager();

        void reset();

        void changeWeapon(std::tr1::shared_ptr<Player> player);

    private:
        //Score limite pour activer les armes
        int secondaryScore, missileScore, thirdScore;

        std::tr1::shared_ptr<Player> player0, player1;

        Weapon_manager();

        static Weapon_manager* _singleton;
};

#endif // WEAPON_MANAGER_H_INCLUDED
