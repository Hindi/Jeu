#ifndef MISSILE_MANAGER_H_INCLUDED
#define MISSILE_MANAGER_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include <tr1/memory>

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
        bool haveMissilesInProgress();

        void createMissile();//V�rifie s'il faut cr�er un missile ou non
        void moveMissile();//D�place tous les projectiles
        void drawMissile();//Dessine tous les projectiles
        void manage();//On bouge et dessine

        void addMissile(std::tr1::shared_ptr<Missile> missible);//Rajoute un missile dans la liste des missiles du joueur
        std::list<std::tr1::shared_ptr<Missile> >* getMissile();//Retourne les missiles
        void followPlayer();
        void revenir(Missile &missile);
        void setPositionLibre(int position, bool mode);
        void setPlayer(Player *externPlayer);

        static void kill();
        static Missile_manager* getInstance();

    private:
        Player *player;
        std::list<std::tr1::shared_ptr<Missile> > m_missiles;
        Timer timerCreate;
        int nombreMissiles, fireDelay;
        sf::Vector2f positionsLibres[7];
        bool boolPositionLibres[7];


        Missile_manager();
        ~Missile_manager();

        static Missile_manager* _singleton;
};

#endif // MISSILE_MANAGER_H_INCLUDED
