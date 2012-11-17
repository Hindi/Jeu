#include "flying_saucer.h"

using namespace std;
using namespace sf;

FlyingSaucer::FlyingSaucer(Vector2f position, const std::string &move, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Enemy(30, 10, 500, 2, 2, "images/enemy2.png", position, "flyingSaucer", move, 1, m_coefSpeed, 2, false, player, player2, false)
{

}

FlyingSaucer::~FlyingSaucer()
{

}

void FlyingSaucer::fire()
{
    //La position de départ du projectile
    Vector2f positionProjectile(m_position);
    positionProjectile.x += (image->GetWidth()/2)-20;
    positionProjectile.y += image->GetHeight()/2-20;
    const string filepath = "images/projectile2.png";

    std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, Vector2f(16, 0), m_coefSpeed));
    projectile->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    std::tr1::shared_ptr<Projectile> projectile1(new Projectile(filepath, positionProjectile, Vector2f(-16, 0), m_coefSpeed));
    projectile1->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile1);
    std::tr1::shared_ptr<Projectile> projectile2(new Projectile(filepath, positionProjectile, Vector2f(0, 16), m_coefSpeed));
    projectile2->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile2);
    std::tr1::shared_ptr<Projectile> projectile3(new Projectile(filepath, positionProjectile, Vector2f(0, -16), m_coefSpeed));
    projectile3->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile3);
    std::tr1::shared_ptr<Projectile> projectile4(new Projectile(filepath, positionProjectile, Vector2f(11, 11), m_coefSpeed));
    projectile4->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile4);
    std::tr1::shared_ptr<Projectile> projectile5(new Projectile(filepath, positionProjectile, Vector2f(-11, 11), m_coefSpeed));
    projectile5->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile5);
    std::tr1::shared_ptr<Projectile> projectile6(new Projectile(filepath, positionProjectile, Vector2f(11, -11), m_coefSpeed));
    projectile6->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile6);
    std::tr1::shared_ptr<Projectile> projectile7(new Projectile(filepath, positionProjectile, Vector2f(-11, -11), m_coefSpeed));
    projectile7->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile7);

    std::tr1::shared_ptr<Projectile> projectile8(new Projectile(filepath, positionProjectile, Vector2f(-7, -14), m_coefSpeed));
    projectile8->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile8);
    std::tr1::shared_ptr<Projectile> projectile9(new Projectile(filepath, positionProjectile, Vector2f(-5, -15), m_coefSpeed));
    projectile9->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile9);
    std::tr1::shared_ptr<Projectile> projectile10(new Projectile(filepath, positionProjectile, Vector2f(7, -14), m_coefSpeed));
    projectile10->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile10);
    std::tr1::shared_ptr<Projectile> projectile11(new Projectile(filepath, positionProjectile, Vector2f(5, -15), m_coefSpeed));
    projectile11->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile11);
    std::tr1::shared_ptr<Projectile> projectile12(new Projectile(filepath, positionProjectile, Vector2f(7, 14), m_coefSpeed));
    projectile12->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile12);
    std::tr1::shared_ptr<Projectile> projectile13(new Projectile(filepath, positionProjectile, Vector2f(5, 15), m_coefSpeed));
    projectile13->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile13);
    std::tr1::shared_ptr<Projectile> projectile14(new Projectile(filepath, positionProjectile, Vector2f(-7, 14), m_coefSpeed));
    projectile14->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile14);
    std::tr1::shared_ptr<Projectile> projectile15(new Projectile(filepath, positionProjectile, Vector2f(-5, 15), m_coefSpeed));
    projectile15->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile15);

    std::tr1::shared_ptr<Projectile> projectile16(new Projectile(filepath, positionProjectile, Vector2f(-14, -7), m_coefSpeed));
    projectile16->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile16);
    std::tr1::shared_ptr<Projectile> projectile17(new Projectile(filepath, positionProjectile, Vector2f(-15, -5), m_coefSpeed));
    projectile17->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile17);
    std::tr1::shared_ptr<Projectile> projectile18(new Projectile(filepath, positionProjectile, Vector2f(14, -7), m_coefSpeed));
    projectile18->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile18);
    std::tr1::shared_ptr<Projectile> projectile19(new Projectile(filepath, positionProjectile, Vector2f(15, -5), m_coefSpeed));
    projectile19->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile19);
    std::tr1::shared_ptr<Projectile> projectile20(new Projectile(filepath, positionProjectile, Vector2f(14, 7), m_coefSpeed));
    projectile20->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile20);
    std::tr1::shared_ptr<Projectile> projectile21(new Projectile(filepath, positionProjectile, Vector2f(15, 5), m_coefSpeed));
    projectile21->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile21);
    std::tr1::shared_ptr<Projectile> projectile22(new Projectile(filepath, positionProjectile, Vector2f(-14, 7), m_coefSpeed));
    projectile22->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile22);
    std::tr1::shared_ptr<Projectile> projectile23(new Projectile(filepath, positionProjectile, Vector2f(-15, 5), m_coefSpeed));
    projectile23->setPosition(positionProjectile);
    Projectile_manager::getInstance()->addEnemyProjectile(projectile23);

    //On le rajoute à la liste des projectiles gérée par le projectile manager.
    lastShot = timer.getTime();
}
