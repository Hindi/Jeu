#include "unit.h"

using namespace std;
using namespace sf;

Unit::Unit(int life, int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app):m_life(life), m_app(app), m_xSpeed(xSpeed), m_ySpeed(ySpeed), m_scale(1,1), m_position(position), coefSpeed(50)
{
    animation = new Animation;
    image = new Image;
    if(image->LoadFromFile(filepath))
    {
        animation->setImage(*image);
    }
    else
    {
        cerr << "Impossible de charge : " << filepath << endl;
    }
}

Unit::~Unit()
{
    delete image;
    delete animation;
}

int Unit::getLife()
{
    return m_life;
}

void Unit::recieveDamages(int dmg)
{
    m_life -= dmg;
}

bool Unit::isDead()
{
    if(m_life <= 0)
        return true;
    else
        return false;
}
