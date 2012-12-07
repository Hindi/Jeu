#include "lilith.h"

using namespace std;
using namespace sf;

Lilith::Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2) :
            Boss(2000, 5, 10000, 3, 3, "images/lilith2.0/corps.png", Vector2f(250, -180), "boss", "don'tmove", 1, 30, 2, player, player2, false, "lilith"),
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
    if(timerRandomShot.getTime() > 0.1)
    {
        Vector2f vitesse(0, 15);
        int value = rand()%10+1;
        std::tr1::shared_ptr<Projectile> projectile(new Projectile("images/projectile.png", positionProjectile, vitesse, m_coefSpeed));
        positionProjectile.y = m_position.y+70;
        switch(value)
        {
            case 1:
                positionProjectile.x = m_position.x+139;
                break;
            case 2:
                projectile->setSpeed(Vector2f(15,15));
                positionProjectile.x = m_position.x;
                positionProjectile.y = m_position.y+85;
                projectile->rotate(50);
                break;
            case 3:
                positionProjectile.x = m_position.x+110;
                break;
            case 4:
                positionProjectile.x = m_position.x+76;
                positionProjectile.y = m_position.y+55;
                break;
            case 5:
                positionProjectile.x = m_position.x+223;
                break;
            case 6:
                positionProjectile.x = m_position.x+251;
                break;
            case 7:
                positionProjectile.x = m_position.x+286;
                break;
            case 8:
                positionProjectile.x = m_position.x+251;
                break;
            case 9:
                positionProjectile.x = m_position.x+310;
                break;
            case 10:
                projectile->setSpeed(Vector2f(-15, 15));
                positionProjectile.x = m_position.x+360;
                projectile->rotate(-50);
                break;
        }
        projectile->setPosition(positionProjectile);
        timerRandomShot.reinitialize();
        Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    }

    this->firinhMahLasor(1);
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
    else if(laserFocusing ||firinh)
        this->dontMove();
    else
        this->dontMove();
    this->follow();
}
