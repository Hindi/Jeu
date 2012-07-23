#include "projectile.h"

using namespace std;
using namespace sf;

Projectile::Projectile(const string &filepath, Vector2f position, Vector2f speed, const int coefSpeed, image_manager &ImageManager): m_speed(speed), scale(1,1), m_coefSpeed(coefSpeed), m_position(position)
{
    image = new Image();
    *image = ImageManager.getImage(filepath);
    image->CreateMaskFromColor(Color(255, 0, 255));
    sprite.SetImage(*image);
    sprite.Scale(scale);
}

Projectile::~Projectile()
{

}

Sprite Projectile::getSprite()
{
    return sprite;
}

void Projectile::Render(sf::RenderTarget& target) const
{
   target.Draw(sprite);
}

int Projectile::getSpeed(int axis) const
{
    if(axis==0)
        return m_speed.x;
    else
        return m_speed.y;
}

const int Projectile::getCoefSpeed() const
{
    return m_coefSpeed;
}

void Projectile::setPosition(Vector2f position)
{
    m_position = position;
}

Vector2f Projectile::getPosition()
{
    return m_position;
}

IntRect Projectile::getBoundingBox() const
{
    //Rectangle de collision pour chaque projectile
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + sprite.GetSize().x;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + sprite.GetSize().y;

    return boundingBox;
}


