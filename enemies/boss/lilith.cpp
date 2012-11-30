#include "lilith.h"

using namespace std;
using namespace sf;

Lilith::Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2) :
            Boss(50, 5, 10000, 3, 3, "images/lilith/corps.png", Vector2f(500, -230), "boss", "roundtrip", 1, 30, 2, player, player2, false),
            m_level(1)
{
    timerRandomShot.start();
    timerMove.start();
}

Lilith::~Lilith()
{

}

void Lilith::fire()
{
    Vector2f positionProjectile(0,0);
    if(timer.getTime() > m_fireRate)
    {
        timer.reinitialize();
        this->VFire();
    }
    if(timerRandomShot.getTime() > 0.3)
    {
        int value = rand()%6+1;
        switch(value)
        {
            case 1:
                positionProjectile.x = m_position.x+134;
                positionProjectile.y = m_position.y+70;
                break;
            case 2:
                positionProjectile.x = m_position.x;
                positionProjectile.y = m_position.y+55;
                break;
            case 3:
                positionProjectile.x = m_position.x+50;
                positionProjectile.y = m_position.y+70;
                break;
            case 4:
                positionProjectile.x = m_position.x+185;
                positionProjectile.y = m_position.y+55;
                break;
            case 5:
                positionProjectile.x = m_position.x+163;
                positionProjectile.y = m_position.y+70;
                break;
            case 6:
                positionProjectile.x = m_position.x+20;
                positionProjectile.y = m_position.y+70;
                break;
        }
        timerRandomShot.reinitialize();
        std::tr1::shared_ptr<Projectile> projectile(new Projectile("images/projectile.png", positionProjectile, Vector2f(0, 15), m_coefSpeed));
        projectile->setPosition(positionProjectile);
        Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    }

    this->firinhMahLasor();
}

IntRect Lilith::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x;
    boundingBox.Right = boundingBox.Left + image->GetWidth();
    boundingBox.Top = m_position.y ;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight()/1.5;

    return boundingBox;
}


IntRect Lilith::getWeakBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x  + image->GetWidth()/2 - 40;
    boundingBox.Right = boundingBox.Left + 70;
    boundingBox.Top = m_position.y + image->GetHeight()-20;
    boundingBox.Bottom = boundingBox.Top + 20;

    return boundingBox;
}

void Lilith::move()
{
    if(timerMove.getTime() < 1.5)
        this->moveDown();
    else
        this->roundTrip();
    this->follow();
}
