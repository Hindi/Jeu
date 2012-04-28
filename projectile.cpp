#include "projectile.h"

using namespace std;
using namespace sf;

Projectile::Projectile(const string &filepath, Vector2f position, int speed): m_speed(speed), scale(1,1), coefSpeed(90)
{
    static Image image;
    if(!image.LoadFromFile(filepath))
    {
        cerr << "Image loading failed : " << filepath << endl;
    }
    else
    {
        image.CreateMaskFromColor(Color(255, 0, 255));
        sprite.SetImage(image);
        sprite.SetPosition(position);
        sprite.Scale(scale);
    }
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

const int Projectile::getSpeed() const
{
    return m_speed;
}

void Projectile::move(Vector2f speed)
{
    sprite.Move(speed);
}

const int Projectile::getCoefSpeed() const
{
    return coefSpeed;
}

IntRect Projectile::getBoundingBox() const
{
    //Rectangle de collision pour chaque projectile
    IntRect boundingBox;
    boundingBox.Left = (int)sprite.GetPosition().x;
    boundingBox.Right = boundingBox.Left + sprite.GetSize().x;
    boundingBox.Top = (int)sprite.GetPosition().y;
    boundingBox.Bottom = boundingBox.Top + sprite.GetSize().y;

    return boundingBox;
}
