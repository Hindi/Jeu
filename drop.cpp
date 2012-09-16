#include "drop.h"

using namespace sf;
using namespace std;

Drop::Drop(int score, image_manager &image_manager, sf::Vector2f position):
            m_speed(200),
            m_score(score),
            m_image_manager(image_manager),
            m_frameWidth(50),
            m_position(position),
            m_frameHeight(50)
{
    m_image = new Image();
    //Choix de l'image en fonction du score
    switch(score)
    {
        case 100:
            *m_image = m_image_manager.getImage("images/Vie.png");
            break;
        case 500:
            *m_image = m_image_manager.getImage("images/Vie-fade.png");
            break;
    }

    m_image->CreateMaskFromColor(Color(255, 0, 255));
    sprite.SetImage(*m_image);
    sprite.SetPosition(m_position);
}

Drop::~Drop()
{

}

int Drop::getScore()
{
    return m_score;
}

Sprite Drop::getSprite()
{
    return sprite;
}

Vector2f Drop::getPosition()
{
    return m_position;
}

void Drop::setPosition(Vector2f position)
{
    m_position = position;
    sprite.Move(0,10);
}

int Drop::getSpeed()
{
    return m_speed;
}

void Drop::move(Vector2f position, Vector2f speed)
{
    m_position = position;
    sprite.Move(speed);
}

IntRect Drop::getBoundingBox()
{
    //Récupère le rectangle de collision pour le drop
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + m_frameWidth;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + m_frameHeight;

    return boundingBox;
}
