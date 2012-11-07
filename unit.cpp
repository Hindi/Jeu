#include "unit.h"

using namespace std;
using namespace sf;

Unit::Unit(int life, int xSpeed, int ySpeed,Vector2f position):
            m_scale(1,1),
            m_position(position),
            m_life(life),
            m_xSpeed(xSpeed),
            m_ySpeed(ySpeed),
            coefSpeed(50)
{
    m_animatedExplosion = new Animated();
    imageExplosion = new Image();
   *imageExplosion = image_manager::getInstance()->getImage("images/Explosion.png");


    EXPLOS_WIDTH = imageExplosion->GetWidth()/7;
    EXPLOS_HEIGHT = imageExplosion->GetHeight();

    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(0, 0, EXPLOS_WIDTH, EXPLOS_HEIGHT) ));
    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(EXPLOS_WIDTH, 0, EXPLOS_WIDTH*2, EXPLOS_HEIGHT) ));
    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(EXPLOS_WIDTH*2, 0, EXPLOS_WIDTH*3, EXPLOS_HEIGHT) ));
    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(EXPLOS_WIDTH*3, 0, EXPLOS_WIDTH*4, EXPLOS_HEIGHT) ));
    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(EXPLOS_WIDTH*4, 0, EXPLOS_WIDTH*5, EXPLOS_HEIGHT) ));
    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(EXPLOS_WIDTH*5, 0, EXPLOS_WIDTH*6, EXPLOS_HEIGHT) ));
    m_animExplosion.PushFrame(Frame(imageExplosion, sf::Rect<int>(EXPLOS_WIDTH*6, 0, EXPLOS_WIDTH*7, EXPLOS_HEIGHT) ));

    m_animatedExplosion->SetAnim(&m_animExplosion);
    m_animatedExplosion->SetLoop(false);
    m_animatedExplosion->SetFrameTime(0.07f);
    m_animatedExplosion->SetPosition(position.x, position.y);

}

Unit::~Unit()
{
    delete m_animatedExplosion;
    delete imageExplosion;
}

short Unit::getLife()
{
    return m_life;
}

sf::Vector2f Unit::getSpeed()
{
    return Vector2f(m_xSpeed, m_ySpeed);
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

void Unit::drawExplosion()
{
    m_animatedExplosion->anim(app.GetFrameTime());
    app.Draw(*m_animatedExplosion);
}

int Unit::getExploWidth()
{
    return EXPLOS_WIDTH;
}
int Unit::getExploHeight()
{
    return EXPLOS_HEIGHT;
}

short Unit::getCoefSpeed() const
{
    return coefSpeed;
}
