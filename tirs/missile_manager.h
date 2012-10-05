#ifndef MISSILE_MANAGER_H_INCLUDED
#define MISSILE_MANAGER_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include "missile.h"
#include "../population.h"
#include "math.h"
#include "../timer.h"
#include "../player.h"
#include "../image_manager.h"
#include "../const.h"

class Missile_manager
{
    public:
        Missile_manager();
        ~Missile_manager();

        bool haveMissilesInProgress();

        void createMissile();//Vérifie s'il faut créer un missile ou non
        void moveMissile();//Déplace tous les projectiles
        void drawMissile();//Dessine tous les projectiles
        void manage();//On bouge et dessine

        void addMissile(Missile *missible);//Rajoute un missile dans la liste des missiles du joueur
        std::list<Missile*>* getMissile();//Retourne les missiles
        void followPlayer();
        void revenir(Missile &missile);
        void setPositionLibre(int position, bool mode);

    private:
        std::list<Missile*> m_missiles;
        Timer timerCreate;
        Missile *missile;
        int nombreMissiles, fireDelay;
        sf::Vector2f positionsLibres[7];
        bool boolPositionLibres[7];
};

#endif // MISSILE_MANAGER_H_INCLUDED
