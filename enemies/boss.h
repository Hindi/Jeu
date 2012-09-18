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
        //Destruteur
        ~Boss();

        //Accesseur sur le sprite
        sf::Sprite* getSprite();

        //Accesseur sur le rectangle occupé par le sprite
        sf::IntRect getBoundingBox();

        //Inflige des dommages à l'ennemi
        void recieveDamages(int dmg);

        //Fonction de tirs avec visée
        void fireCircle();

        //fonction de tir en cercle
        void fireFocus();

        //Défini si le boss peut tirer ou non
        bool canFire();

        //Gestion du timer
        void startTimer();
        void pauseTimer();

        //Accesseur sur la position du boss sur un axe
        int getPositionAxis(int axis);

        //Accesseur sur la position du boss
        sf::Vector2f getPosition();
        void setPosition(int axis, int value);

        //Accesseur sur l'animation de l'ennemi
        Animated *getAnimationExplosion();
        Animated *getAnimation();


    private:
        //Le joueur
        Player &m_player;

        //Liste des projectiles du boss
        std::list<Projectile*> m_projectiles;

        //Liste des vitesses de tous les projectiles
        std::list<sf::Vector2f> m_vitesses;

        //Direction de déplacement
        char* direction;

        //Porjectile
        Projectile *projectile;

        //Li'mage du boss
        sf::Image *image;

        //Sprite du boss
        sf::Sprite sprite;

        //Le moment du dernier tir
        float lastShot;

        //Timers de tir et de déplacement
        Timer timer, timerMove;

        //Constantes de score au touché et à la mort, vitesses des projectiles et fréquence de tir
        int const m_scoreHit, m_scoreExplosion, projectileSpeed, m_coefSpeed, m_fireRate;

        //Sauvegarde sur un timer de déplacement
        float savedTimerMove;

        //Variables d'animation
        Animated *m_animated;
        Anim m_anim;

        //Manager d'images
        image_manager &m_imageManager;

        //Position du jour
        sf::Vector2f playerPosition;

        //Type de tir
        char* m_type;

        //Type de déplacement
        char* m_moveMethod;

        //Etape dans les différents déplacements
        int  m_moveValue;


};
#endif // BOSS_H_INCLUDED
