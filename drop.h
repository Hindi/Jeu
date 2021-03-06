#ifndef DROP_H_INCLUDED
#define DROP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "image_manager.h"

class Drop
{
    public:
        Drop(int score, sf::Vector2f position);

        //Destrcteur
        ~Drop();

        //Accesseurs publics
        unsigned short getScore();
        sf::Sprite getSprite();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        short getSpeed() const;
        void move(sf::Vector2f position, sf::Vector2f speed);
        sf::IntRect getBoundingBox();

    private:
        //image du drop
        sf::Image *m_image;

        //Vitesse, score donn� au joueur, taille du sprite
        int const m_frameWidth, m_frameHeight;
        short const m_speed;
        unsigned short const m_score;

        //Sprite du drop
        sf::Sprite sprite;

        //Position actuelle du drop
        sf::Vector2f m_position;

};

#endif // DROP_H_INCLUDED
