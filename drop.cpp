#include "drop.h"

using namespace sf;
using namespace std;

Drop::Drop(int score, image_manager &image_manager, sf::Vector2f position): m_speed(5), m_score(score), m_image_manager(image_manager), m_position(position)
{
    m_image = new Image();
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
