#ifndef ADDS_H_INCLUDED
#define ADDS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <list.h>

/*****************************************
TODO :
    - Fonction follow pour suivre le boss
    - Différents mode de tirs
    - Quels déplacement ?
/******************************************/

class Adds
{
    public:
    adds();
    ~adds();

    //Suivre le boss
    follow();





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

        //Position du joueur
        sf::Vector2f playerPosition;

        //Type de tir
        char* m_type;

        //Type de déplacement
        char* m_moveMethod;

        //Etape dans les différents déplacements
        int  m_moveValue;

        //Accesseur sur le type de tir
        char* getType();

        //Accesseur sur le score donné par l'ennemis au joueur quand il touche
        int getScoreHit();
        //Accesseur sur le score donné au joueur quand l'ennemi meurt
        int getScoreExplosion();


}

#endif // ADDS_H_INCLUDED
