#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "../animation.h"
#include "../image_manager.h"
#include <iostream>
#include <vector>

//Type projectile géré par player et enemy

class Projectile : public sf::Drawable
{
    public:
        Projectile(const std::string &filepath, sf::Vector2f position, sf::Vector2f speed, const int coefSpeed, image_manager &ImageManager, bool followAnim = false);

        //Destructeur
        ~Projectile();

        //Sprite des projectiles
        sf::Sprite getSprite();

        //Parce que c'est un drawable, permet de les dessiner directement
        void Render(sf::RenderTarget& target) const;

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

        void setProjPosition(std::vector<sf::Vector2f> positions);

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
};

#endif // PROJECTILE_H_INCLUDED
