#include "missile.h"

using namespace std;
using namespace sf;

Missile::Missile(const string &filepath, Vector2f position, int speed, const int coefSpeed, image_manager &ImageManager, int listPosition):
            m_speed(speed),
            m_coefSpeed(coefSpeed),
            m_position(position),
            focusing(false),
            listPosition(listPosition)
{
    image = new Image();
    *image = ImageManager.getImage(filepath);
    image->CreateMaskFromColor(Color(255, 0, 255));
    sprite.SetImage(*image);
    sprite.Scale(scale);
}

Missile::~Missile()
{

}

Sprite Missile::getSprite()
{
    return sprite;
}

void Missile::Render(sf::RenderTarget& target) const
{
   target.Draw(sprite);
}

short Missile::getSpeed() const
{
        return m_speed;
}

short Missile::getCoefSpeed() const
{
    return m_coefSpeed;
}

void Missile::setPosition(Vector2f position)
{
    m_position = position;
}

Vector2f Missile::getPosition()
{
    return m_position;
}

IntRect Missile::getBoundingBox() const
{
    //Rectangle de collision pour chaque projectile
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + sprite.GetSize().x;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + sprite.GetSize().y;

    return boundingBox;
}

short Missile::getDamage() const
{
    return 10;
}

bool Missile::isInScreen()
{
    if(m_position.x > 0 && m_position.x< 1300 && m_position.y > 0 && m_position.y < 1100)
        return true;
    else
        return false;
}

void Missile::setFocus(bool choix)
{
    focusing = choix;
}

bool Missile::getFocus()
{
    return focusing;
}

short Missile::getListPosition() const
{
    return listPosition;
}
