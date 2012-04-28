#include "unit.h"

using namespace std;
using namespace sf;

Unit::Unit(int life, int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app, IntRect subRect):m_life(life), m_app(app), m_xSpeed(xSpeed), m_ySpeed(ySpeed), m_scale(1,1), m_position(position), coefSpeed(75), m_subRect(subRect)
{
    image = new Image;
    if(!(*image).LoadFromFile(filepath))
    {
        cerr << "Image loading failed : " << filepath << endl;
    }
    else
    {
        (*image).CreateMaskFromColor(Color(255, 0, 255));
        sprite.SetImage(*image);
        sprite.SetPosition(position);
        sprite.Scale(m_scale);
        sprite.SetSubRect(subRect);
    }
}

Unit::~Unit()
{

}

int Unit::getLife()
{
    return m_life;
}

void Unit::recieveDamages(int dmg)
{
    m_life -= dmg;
}

void Unit::moveLeft()
{
    m_subRect.Right = 354;
    m_subRect.Left = 236;
    sprite.SetSubRect(m_subRect);
    double elapsedTime = m_app.GetFrameTime();
    sprite.Move(-m_xSpeed*elapsedTime*coefSpeed, 0);
    m_position.x -= m_xSpeed*elapsedTime*coefSpeed;
}

void Unit::moveRight()
{
    m_subRect.Right = 236;
    m_subRect.Left = 118;
    sprite.SetSubRect(m_subRect);
    double elapsedTime = m_app.GetFrameTime();
    sprite.Move(m_xSpeed*elapsedTime*coefSpeed, 0);
    m_position.x += m_xSpeed*elapsedTime*coefSpeed;
}

void Unit::moveUp()
{
    double elapsedTime = m_app.GetFrameTime();
    sprite.Move(0, -m_ySpeed*elapsedTime*coefSpeed);
    m_position.y -= m_ySpeed*elapsedTime*coefSpeed;
}


void Unit::moveDown()
{
    double elapsedTime = m_app.GetFrameTime();
    sprite.Move(0, m_ySpeed*elapsedTime*coefSpeed);
    m_position.y += m_ySpeed*elapsedTime*coefSpeed;
}

bool Unit::isDead()
{
    if(m_life <= 0)
        return true;
    else
        return false;
}
