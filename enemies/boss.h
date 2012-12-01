#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>

#include "../player.h"
#include "enemy.h"
#include "../timer.h"
#include "adds.h"
#include "../son/sound_manager.h"

/*
****************************************
TODO :
    - Fonction pour créer les adds
****************************************
*/
class Boss : public Enemy
{
    public:
        Boss(int life, int scoreHit, int scoreExplosion,  int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, const std::string moveMethod,
             int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport, const char* name);
        //Destruteur
        virtual ~Boss();

        virtual void draw();
        sf::Vector2f getPosition();
        virtual void setTeleporting(bool state);
        void firinhMahLasor(int fireTime);
        void pushAdd(std::tr1::shared_ptr<Adds> add);
        virtual void follow();
        bool canFire();
        bool canTeleport();
        void teleport();
        void drawHealthBar();


    protected:
        sf::SoundBuffer vuuuBuffer;
        sf::Sound vuuuSound;

        sf::Sprite spriteHealthBackground;
        sf::Sprite spriteHealthBar;

        sf::Image *imageHealthBackground;
        sf::Image *imageHealthBar;

        std::list<std::tr1::shared_ptr<Adds> > m_adds;
        const char* m_name;
        const char* m_type;
        short m_level;
        bool startedLasor;
        Timer timerLaser, timerFireTime;
        int laserRate, currentFrame;
        int startLife;

        //Variables laser
        bool startingLasor, laserFocusing, firinh;
        Timer timerAddMove;
        Animated *m_animatedFocus;
        Anim m_animFocus;
        sf::Image* imageFocus;
        short loop;

};
#endif // BOSS_H_INCLUDED
