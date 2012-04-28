#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

//Type projectile géré par player et enemy

class Projectile : public sf::Drawable
{
    public:
        Projectile(const std::string &filepath, sf::Vector2f position, int speed);
        ~Projectile();
        sf::Sprite getSprite();
        void Render(sf::RenderTarget& target) const;
        const int getSpeed() const;
        const int getCoefSpeed() const;
        void move(sf::Vector2f speed);
        sf::IntRect getBoundingBox() const;

    protected:
        static sf::Image image;
        sf::Sprite sprite;
        const sf::Vector2f scale;
        const int m_speed;
        const int coefSpeed;
        int m_width, m_height;
};

#endif // PROJECTILE_H_INCLUDED
