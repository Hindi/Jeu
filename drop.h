#ifndef DROP_H_INCLUDED
#define DROP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "image_manager.h"

class Drop
{
    public:
        Drop(int score, image_manager &image_manager, sf::Vector2f position);
        ~Drop();
        int getScore();
        sf::Sprite getSprite();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        int getSpeed();
        void move(sf::Vector2f position, sf::Vector2f speed);
        sf::IntRect getBoundingBox();

    private:
        sf::Image *m_image;
        int m_speed, m_score,m_frameWidth, m_frameHeight;
        image_manager &m_image_manager;
        sf::Sprite sprite;
        sf::Vector2f m_position;

};

#endif // DROP_H_INCLUDED
