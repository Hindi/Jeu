#ifndef PROJECTILE_MANAGER_H_INCLUDED
#define PROJECTILE_MANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../son/sound_manager.h"
#include <SFML/Audio.hpp>
#include <iostream>
#include <list>
#include <tr1/memory>

#include "projectile.h"
#include "missile.h"
#include <vector>
#include "../const.h"

class Projectile_manager
{
    public:

        //V�rifie si il y a des projectiles en cours
        bool haveEnemyProjectilesInProgress();
        bool havePlayerProjectilesInProgress();

        //D�place tous les projectiles
        void moveProjectile();

        //Dessine tous les projectiles
        void drawProjectile();

        //Rajoute un projectile dans la liste des projectiles ennemi
        void addEnemyProjectile(std::tr1::shared_ptr<Projectile>  projectile);

        //Rajoute un projectile dans la liste des projectiles joueur
        void addPlayerProjectile(std::tr1::shared_ptr<Projectile>  projectile);

        //Retourne les projectiles ennemi
        std::list<std::tr1::shared_ptr<Projectile> >* getEnemyProjectiles();

        //Retourne les projectiles joueur
        std::list<std::tr1::shared_ptr<Projectile> >* getPlayerProjectiles();

        void animationFollow();

        static void kill();
        static Projectile_manager* getInstance();

        void freeze();
        void unfreeze();

        void reset();

        void killThemAll();

    private:
        sf::SoundBuffer piouBuffer;
        sf::Sound piouSound;
        sf::SoundBuffer piou2Buffer;
        sf::Sound piou2Sound;

        //Liste des projectiles ennemis
        std::list<std::tr1::shared_ptr<Projectile> > m_enemyProjectiles;

        //Liste des projectiles du joueur
        std::list<std::tr1::shared_ptr<Projectile> > m_playerProjectiles;


        Projectile_manager();

        //Destructeur
        ~Projectile_manager();

        static Projectile_manager* _singleton;

};


#endif // PROJECTILE_MANAGER_H_INCLUDED
