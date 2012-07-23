#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "animation.h"
#include "image_manager.h"
#include <iostream>

//Type projectile géré par player et enemy

class Projectile : public sf::Drawable
{
    public:
        Projectile(const std::string &filepath, sf::Vector2f position, sf::Vector2f speed, const int coefSpeed, image_manager &ImageManager);
        ~Projectile();
        sf::Sprite getSprite();
        void Render(sf::RenderTarget& target) const;
        int getSpeed(int axis) const;
        const int getCoefSpeed() const;
        sf::IntRect getBoundingBox() const;
        void setPosition(sf::Vector2f position);
        sf::Vector2f getPosition();

    protected:
        sf::Image *image;
        sf::Sprite sprite;
        const sf::Vector2f scale;
        sf::Vector2f m_speed;
        const int m_coefSpeed;
        int m_width, m_height;
        sf::Vector2f m_position;
};

#endif // PROJECTILE_H_INCLUDED
