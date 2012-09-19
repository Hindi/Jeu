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
#include "adds.h"
#include "../enemy.h"

/*
****************************************
TODO :
    - Fonction pour créer les adds
/*****************************************
*/
class Boss : public Enemy
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

        void createAdd();

        //Accesseur sur le type de tir
        char* getType();

        //Accesseur sur le score donné par l'ennemis au joueur quand il touche
        int getScoreHit();
        //Accesseur sur le score donné au joueur quand l'ennemi meurt
        int getScoreExplosion();


    private:

};
#endif // BOSS_H_INCLUDED
