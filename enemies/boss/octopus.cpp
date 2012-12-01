#include "octopus.h"

using namespace std;
using namespace sf;

Octopus::Octopus(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Boss(50, 5, 10000, 3, 3, "images/octopus/Oeil.png", Vector2f(500, -180), "boss", "roundtrip", 1, 30, 2, player, player2, false)
{
    timerMove.start();
}

Octopus::~Octopus()
{
    //dtor
}

void Octopus::fire()
{
    if(timerFireTime.getTime() > 2 && timerFireTime.getTime() < 7)
    {
        Vector2f position(m_position.x+100, m_position.y+200);
        std::tr1::shared_ptr<Projectile> projectile(new Projectile("images/projectile.png", position, Vector2f(0, 15), m_coefSpeed));
        projectile->setPosition(position);
        Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    }
    else if(timerFireTime.getTime() > 7)
    {
        timerFireTime.reinitialize();
    }
}

IntRect Octopus::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + image->GetWidth();
    boundingBox.Top = m_position.y ;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/1.5;

    return boundingBox;
}

IntRect Octopus::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x  + image->GetWidth()/2 - 40;
    boundingBox.Right = boundingBox.Left + 70;
    boundingBox.Top = m_position.y + image->GetHeight()-20;
    boundingBox.Bottom = boundingBox.Top + 20;

    return boundingBox;
}
void Octopus::move()
{
    if(timerMove.getTime() < 0.5)
    {
        this->moveDown();
        this->follow();
    }
}

void Octopus::follow()
{
    list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
    for(; lit != m_adds.end(); lit++)
    {
        Vector2f position(m_position.x +(*lit)->getRelativePosition().x, m_position.y + (*lit)->getRelativePosition().y);
        (*lit)->getAnimation()->SetPosition(position);
        (*lit)->setPosition(position);
    }
}
