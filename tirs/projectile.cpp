#include "projectile.h"

using namespace std;
using namespace sf;

Projectile::Projectile(const string &filepath, Vector2f position, Vector2f speed, const int coefSpeed, bool followAnim):
            m_speed(speed),
            scale(1,1),
            m_coefSpeed(coefSpeed),
            m_position(position),
            m_followAnim(followAnim),
            followRate(0.1)
{
    this->setPosition(position);
    if(!m_followAnim)
    {

        firstProj = new Image();
        *firstProj = image_manager::getInstance()->getImage(filepath);
        spriteFirst.SetImage(*firstProj);
        spriteFirst.Scale(scale);
    }
    if(m_followAnim)
    {
        firstProj = new Image();
        *firstProj = image_manager::getInstance()->getImage(filepath);
        unsigned short width = firstProj->GetWidth();
        unsigned short height = firstProj->GetHeight();
        spriteFirst.SetImage(*firstProj);
        spriteFirst.SetSubRect(IntRect(0, 0, width/5, height));
        spriteFirst.Scale(scale);

        secondProj = new Image();
        *secondProj = image_manager::getInstance()->getImage(filepath);
        spriteSecond.SetImage(*secondProj);
        spriteSecond.SetSubRect(IntRect(width/5, 0, 2*width/5, height));
        spriteSecond.Scale(scale);

        thirdProj = new Image();
        *thirdProj = image_manager::getInstance()->getImage(filepath);
        spriteThird.SetImage(*thirdProj);
        spriteThird.SetSubRect(IntRect(2*width/5, 0, 3*width/5, height));
        spriteThird.Scale(scale);

        fourthProj = new Image();
        *fourthProj = image_manager::getInstance()->getImage(filepath);
        spriteFourth.SetImage(*fourthProj);
        spriteFourth.SetSubRect(IntRect(3*width/5, 0, 4*width/5, height));
        spriteFourth.Scale(scale);

        fifthProj = new Image();
        *fifthProj = image_manager::getInstance()->getImage(filepath);
        spriteFifth.SetImage(*fifthProj);
        spriteFifth.SetSubRect(IntRect(4*width/5, 0, width, height));
        spriteFifth.Scale(scale);

        sprites.push_back(&spriteFifth);
        sprites.push_back(&spriteFourth);
        sprites.push_back(&spriteThird);
        sprites.push_back(&spriteSecond);
        sprites.push_back(&spriteFirst);
        for(vector<Sprite*>::size_type i=0;i<sprites.size();i++)
        {
            Vector2f currentPosition(sprites[i]->GetPosition());
            sprites[i]->SetPosition(m_position);
        }
    }


    timerFollow.start();
}

Projectile::~Projectile()
{
    delete firstProj;
    if(m_followAnim)
    {
        delete secondProj;
        delete thirdProj;
        delete fourthProj;
        delete fifthProj;
    }
}

Sprite Projectile::getSprite()
{
    return spriteFirst;
}

void Projectile::rotate(short angle)
{
    spriteFirst.Rotate(angle);
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
    spriteFirst.SetPosition(position);
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

void Projectile::setProjPosition(Vector2f speed)
{
    if(m_followAnim && !m_positions.empty())
    {
        for(vector<Vector2f*>::size_type j=0;j<m_positions.size();j++)
        {
            m_positions[j].x += speed.x;
            m_positions[j].y += speed.y;
        }

        for(vector<Sprite*>::size_type i=0;i<sprites.size();i++)
        {
            Vector2f currentPosition(sprites[i]->GetPosition());
            sprites[i]->SetPosition(m_positions[i]);
        }
    }
    else
    {
        m_position.x += speed.x;
        m_position.y += speed.y;

        spriteFirst.SetPosition(m_position);
    }
}


bool Projectile::hasAnimationFollow()
{
    return m_followAnim;
}


deque<Vector2f> Projectile::getPositions()
{
    return m_positions;
}


void Projectile::move(Vector2f speed)
{
    if(timerFollow.getTime() > followRate && m_positions.size() < 5)
    {
        m_positions.push_front(m_position);
        timerFollow.reinitialize();
    }
    this->setProjPosition(speed);
}

void Projectile::draw()
{
    app.Draw(spriteFirst);

    if(m_followAnim)
    {
        app.Draw(spriteSecond);
        app.Draw(spriteThird);
        app.Draw(spriteFourth);
        app.Draw(spriteFifth);
    }
}

void Projectile::freeze()
{
    m_speed.x /=3;
    m_speed.y /=3;
}

void Projectile::unfreeze()
{
    m_speed.x *=3;
    m_speed.y *=3;
}
