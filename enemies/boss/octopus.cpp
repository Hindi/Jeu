#include "octopus.h"

using namespace std;
using namespace sf;

Octopus::Octopus(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Boss(50, 5, 10000, 3, 3, "images/octopus/Oeil.png", Vector2f(500, -180), "boss", "roundtrip", 1, 30, 2, player, player2, false, "octopus")
{
    timerMove.start();
    lastTentaMove = 0;


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
    else if(timerMove.getTime() - lastTentaMove > 0.1)
    {
        list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
        Vector2f position;
        float y=0;
        for(; lit != m_adds.end(); lit++)
        {
            position.y = (*lit)->getPosition().y;
            y = position.y / 100;
            float t = timerMove.getTime() + (*lit)->getRelativePosition().x;
            position.x = m_position.x + (*lit)->getRelativePosition().x + pow(2,position.y/70) * ( 0.6*sin(y-t) + 0.5*sin(1.7*(y-t)) + 0.3*sin(2.4*(y-t)) + 0.4*sin(4.1*(y-t)));
            (*lit)->getAnimation()->SetPosition(position);
            (*lit)->setPosition(position);
        }

        lastTentaMove = timerMove.getTime();
    }

    //On change l'image du bout de tentacule
    list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
    list<tr1::shared_ptr<Adds> >::const_iterator litref1(m_adds.begin());
    list<tr1::shared_ptr<Adds> >::const_iterator litref2(m_adds.begin());
    int yref1(0), yref2(0);
    for(; lit != m_adds.end(); lit++)
    {
        if((*lit)->getPosition().y > yref1 && (*lit)->getPosition().x < 600)
        {
            yref1 = (*lit)->getPosition().y;
            litref1 = lit;
        }
        if((*lit)->getPosition().y > yref2 && (*lit)->getPosition().x > 600)
        {
            yref2 = (*lit)->getPosition().y;
            litref2 = lit;
        }
    }
    (*litref1)->changeImage("images/octopus/TentaculeBout.png", 1);
    (*litref2)->changeImage("images/octopus/TentaculeBout.png", 1);
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
