#ifndef MISSILE_H_INCLUDED
#define MISSILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../image_manager.h"

class Missile : public sf::Drawable
{
    public:
        Missile(const std::string &filepath, sf::Vector2f position, int speed, const int coefSpeed, image_manager &ImageManager, int listPosition);
        ~Missile();
        sf::Sprite getSprite();
        void Render(sf::RenderTarget& target) const;
        int getSpeed() const;
        const int getCoefSpeed() const;
        sf::IntRect getBoundingBox() const;
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();
        int getDamage();//Définit les dommage occasioné par un missile
        bool isInScreen();//Vérifie si le missile est dans l'écran
        void setFocus(bool choix);
        bool getFocus();
        int getListPosition();

    protected:
        sf::Image *image;
        sf::Sprite sprite;
        const sf::Vector2f scale;
        int m_speed, listPosition;
        const int m_coefSpeed;
        int m_width, m_height;
        sf::Vector2f m_position;
        bool focusing;
};

#endif // MISSILE_H_INCLUDED
