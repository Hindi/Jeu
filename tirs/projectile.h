#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../animation.h"
#include <iostream>
#include <deque>
#include "../timer.h"
#include "../image_manager.h"
#include "../const.h"

//Type projectile géré par player et enemy

class Projectile
{
    public:
        Projectile(const std::string &filepath, sf::Vector2f position, sf::Vector2f speed, const int coefSpeed, bool followAnim = false);

        //Destructeur
        ~Projectile();

        //Sprite des projectiles
        sf::Sprite getSprite();

        //Accesseur sur la vitesse
        short getSpeed(int axis) const;

        //Accesseur sur le coeficient de vitesse
        const short getCoefSpeed() const;

        //Accesseur sur le rectangle du sprite
        sf::IntRect getBoundingBox() const;

        //Setter de position
        void setPosition(sf::Vector2f position);

        //Accesseur sur la position
        sf::Vector2f getPosition();

        void setProjPosition(sf::Vector2f speed);

        bool hasAnimationFollow();


        std::deque<sf::Vector2f> getPositions();

        void move(sf::Vector2f speed);

        void draw();

        void freeze();
        void unfreeze();

        void rotate(short angle);

        void killThemAll();

    protected:

        //Le sprite
        sf::Sprite spriteFirst;
        sf::Sprite spriteSecond;
        sf::Sprite spriteThird;
        sf::Sprite spriteFourth;
        sf::Sprite spriteFifth;

        //L'échelle d'affichage des projectiles
        const sf::Vector2f scale;

        //Vitesse des projcetiles
        sf::Vector2f m_speed;

        //Coeficient de vitesse
        const short m_coefSpeed;

        //Position courante
        sf::Vector2f m_position;

        //Animation de poursuite ou non
        bool m_followAnim;

        sf::Image *firstProj;
        sf::Image *secondProj;
        sf::Image *thirdProj;
        sf::Image *fourthProj;
        sf::Image *fifthProj;

        std::vector<sf::Sprite*> sprites;
        //Positions occupées par la suite d'image pour l'animation de suivi
        std::deque<sf::Vector2f> m_positions;

        Timer timerFollow;
        float followRate;
};

#endif // PROJECTILE_H_INCLUDED
