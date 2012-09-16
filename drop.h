#ifndef DROP_H_INCLUDED
#define DROP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "image_manager.h"

class Drop
{
    public:
        Drop(int score, image_manager &image_manager, sf::Vector2f position);

        //Destrcteur
        ~Drop();

        //Accesseurs publics
        int getScore();
        sf::Sprite getSprite();
        sf::Vector2f getPosition();
        void setPosition(sf::Vector2f position);
        int getSpeed();
        void move(sf::Vector2f position, sf::Vector2f speed);
        sf::IntRect getBoundingBox();

    private:
        //image du drop
        sf::Image *m_image;

        //Vitesse, score donné au joueur, taille du sprite
        int m_speed, m_score,m_frameWidth, m_frameHeight;

        //Manager d'image
        image_manager &m_image_manager;

        //Sprite du drop
        sf::Sprite sprite;

        //Position actuelle du drop
        sf::Vector2f m_position;

};

#endif // DROP_H_INCLUDED
