#ifndef BOSS_H_INCLUDED
#define BOSS_H_INCLUDED
#include <list>
#include <SFML/Graphics.hpp>
#include "../player.h"
#include "../timer.h"
#include "../unit.h"
#include "../projectile.h"
#include "../animation.h"
#include "../Animated.hpp"
#include "../image_manager.h"
#include "../projectile_manager.h"

class Boss : public Unit
{
    public:
        Boss(int life, int scoreHit, int scoreExplosion,  int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, char* moveMethod,
             int moveValue, const int coefSpeed, const int firerate, sf::RenderWindow &app, Player &player, image_manager &imageManager, Projectile_manager &projectile_manager);
        ~Boss();

    private:
        Player &m_player;
        std::list<Projectile*> m_projectiles;
        std::list<sf::Vector2f> m_vitesses;
        char* direction;
        Projectile *projectile;
        sf::Image *image;
        float lastShot;
        Timer timer, timerMove;
        int const m_scoreHit, m_scoreExplosion, projectileSpeed, m_coefSpeed, m_fireRate;
        float savedTimerMove;
        Animated *m_animated;
        Anim m_anim;
        image_manager &m_imageManager;
        sf::Vector2f playerPosition;
        char* m_type;
        char* m_moveMethod;
        int  m_moveValue;


};
#endif // BOSS_H_INCLUDED
