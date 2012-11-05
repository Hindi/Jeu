#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <list>
#include "player.h"
#include "enemies/enemy.h"
#include "collision.h"
#include "population.h"
#include "pannel.h"
#include "timer.h"
#include "menu.h"
#include "script.h"
#include "background.h"
#include "image_manager.h"
#include "tirs/projectile_manager.h"
#include "guard.h"
#include "tirs/missile_manager.h"
#include "tirs/weapon_manager.h"
#include "drop_manager.h"
#include "tirs/score_manager.h"
#include "const.h"
#include "levels/level_manager.h"

class Jeu
{
    public:
        Jeu(int const SCREEN_WIDTH, int const SCREEN_HEIGHT, Menu &menu);

        //Destructeur
        ~Jeu();

        //Démarre la partie
        void start(short niveau);

        //Met en pause la partie
        void pause(sf::Event event, Pannel &pannel,std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2);

        void saveDatas(std::tr1::shared_ptr<Player> player1, std::tr1::shared_ptr<Player> player2);

    protected:
        //Taille de la fenêtre
        int const m_SCREEN_WIDTH, m_SCREEN_HEIGHT;

        //Objet menu pour lancer la partie et mettre en pause
        Menu &m_menu;

        //Pour quitter la partie en cours
        bool m_quit;

        int scorePlayer1, scorePlayer2;

};

#endif // JEU_H_INCLUDED
