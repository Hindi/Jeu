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

class Missile_manager
{
    public:
        Missile_manager(sf::RenderWindow &app, Population &population, Player &player, image_manager &imageManager);
        ~Missile_manager();

        bool haveMissilesInProgress();

        void createMissile();//V�rifie s'il faut cr�er un missile ou non
        void moveMissile();//D�place tous les projectiles
        void drawMissile();//Dessine tous les projectiles
        void manage();//On bouge et dessine

        void addMissile(Missile *missible);//Rajoute un missile dans la liste des missiles du joueur
        std::list<Missile*>* getMissile();//Retourne les missiles
        void followPlayer();
        void revenir(Missile &missile);
        void setPositionLibre(int position, bool mode);

    private:
        sf::RenderWindow &m_app;
        std::list<Missile*> m_missiles;
        Population &m_population;
        Timer timerCreate;
        Player &m_player;
        Missile *missile;
        image_manager &m_imageManager;
        int nombreMissiles, fireDelay;
        sf::Vector2f positionsLibres[7];
        bool boolPositionLibres[7];
};

#endif // MISSILE_MANAGER_H_INCLUDED