#include "projectile.h"

using namespace std;
using namespace sf;

Projectile::Projectile(const string &filepath, Vector2f position, Vector2f speed, const int coefSpeed, image_manager &ImageManager, bool followAnim):
            m_speed(speed),
            scale(1,1),
            m_coefSpeed(coefSpeed),
            m_position(position),
            m_followAnim(followAnim)
{
    if(!m_followAnim)
    {

        firstProj = new Image();
        *firstProj = ImageManager.getImage(filepath);
        spriteFirst.SetImage(*firstProj);
        spriteFirst.Scale(scale);
    }
    if(m_followAnim)
    {
        firstProj = new Image();
        *firstProj = ImageManager.getImage(filepath);
        unsigned short width = firstProj->GetWidth();
        unsigned short height = firstProj->GetHeight();
        spriteFirst.SetImage(*firstProj);
        spriteFirst.SetSubRect(IntRect(0, 0, width/5, height));
        spriteFirst.Scale(scale);

        secondProj = new Image();
        *secondProj = ImageManager.getImage(filepath);
        spriteSecond.SetImage(*secondProj);
        spriteSecond.SetSubRect(IntRect(width/5, 0, 2*width/5, height));
        spriteSecond.Scale(scale);

        thirdProj = new Image();
        *thirdProj = ImageManager.getImage(filepath);
        spriteThird.SetImage(*thirdProj);
        spriteThird.SetSubRect(IntRect(2*width/5, 0, 3*width/5, height));
        spriteThird.Scale(scale);

        fourthProj = new Image();
        *fourthProj = ImageManager.getImage(filepath);
        spriteFourth.SetImage(*fourthProj);
        spriteFourth.SetSubRect(IntRect(3*width/5, 0, 4*width/5, height));
        spriteFourth.Scale(scale);

        fifthProj = new Image();
        *fifthProj = ImageManager.getImage(filepath);
        spriteFifth.SetImage(*fifthProj);
        spriteFifth.SetSubRect(IntRect(4*width/5, 0, width, height));
        spriteFifth.Scale(scale);

        sprites.push_back(&spriteSecond);
        sprites.push_back(&spriteThird);
        sprites.push_back(&spriteFourth);
        sprites.push_back(&spriteFifth);
    }

    sprites.push_back(&spriteFirst);
}

Projectile::~Projectile()
{

}

Sprite Projectile::getSprite()
{
    return spriteFirst;
}

void Projectile::Render(sf::RenderTarget& target) const
{
   target.Draw(spriteFirst);
   if(m_followAnim)
   {
       target.Draw(spriteSecond);
       target.Draw(spriteThird);
       target.Draw(spriteFourth);
       target.Draw(spriteFifth);
   }
}

short Projectile::getSpeed(int axis) const
{
    if(axis==0)
        return m_speed.x;
    else
        return m_speed.y;
}

const short Projectile::getCoefSpeed() const
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
    boundingBox.Right = boundingBox.Left + spriteFirst.GetSize().x;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + spriteFirst.GetSize().y;

    return boundingBox;
}


void Projectile::setProjPosition(std::vector<sf::Vector2f> positions)
{
    if(m_followAnim)
    {
        for(vector<Vector2f>::size_type i =0; i <= positions.size();  i++)
        {
            for(vector<Sprite*>::size_type j = 0; j <= sprites.size(); j++)
            {
                sprites[j]->SetPosition(positions[i]);
            }
        }
    }
}
