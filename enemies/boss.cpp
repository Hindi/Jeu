#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2, bool allowTeleport) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2, allowTeleport),
            startedLasor(false),
            laserRate(1)
{
    timerLaser.start();

}

Boss::~Boss()
{
    delete m_name;
}

void Boss::draw()
{
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
        app.Draw(*m_animated);
}


Vector2f Boss::getPosition()
{
    return m_position;
}

void Boss::setTeleporting(bool state)
{
    teleporting = state;
}

void Boss::firinhMahLasor()
{
    if(!startedLasor && timerLaser.getTime() > laserRate)
    {
        timerAddMove.start();
        startedLasor = true;
    }
    if(startedLasor && timerAddMove.getTime() < 2)
    {
        int speed, sign;
        list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
        for(; lit != m_adds.end(); lit++)
        {
            sign = (image->GetWidth()/3 + m_position.x - (*lit)->getPosition().x);
            speed = (sign / fabs(sign))*15;
            (*lit)->horizontalMove(speed);
        }
    }
}

void Boss::pushAdd(std::tr1::shared_ptr<Adds> add)
{
    m_adds.push_back(add);
}

void Boss::follow()
{
    list<tr1::shared_ptr<Adds> >::const_iterator lit(m_adds.begin());
    for(; lit != m_adds.end(); lit++)
    {
        Vector2f position(m_position.x +(*lit)->getRelativePosition().x, m_position.y + (*lit)->getRelativePosition().y);
        (*lit)->getAnimation()->SetPosition(position);
        (*lit)->setPosition(position);
    }
}
