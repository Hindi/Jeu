#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../image_manager.h"

class Missile : public sf::Drawable
{
    public:
        Missile(const std::string &filepath, sf::Vector2f position, int speed, const int coefSpeed, int listPosition);
        ~Missile();
        sf::Sprite getSprite();
        void Render(sf::RenderTarget& target) const;
        short getSpeed() const;
        short getCoefSpeed() const;
        sf::IntRect getBoundingBox() const;
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        short getDamage() const;//Définit les dommage occasioné par un missile
        bool isInScreen();//Vérifie si le missile est dans l'écran
        void setFocus(bool choix);
        bool getFocus();
        short getListPosition() const;

    protected:
        sf::Image *image;
        sf::Sprite sprite;
        const sf::Vector2f scale;
        short const m_speed, listPosition;
        short const m_coefSpeed;
        sf::Vector2f m_position;
        bool focusing;
};

#endif // MISSILE_H_INCLUDED
