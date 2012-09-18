#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, RenderWindow &app,
                Player &player, image_manager &imageManager,Projectile_manager &projectile_manager) :
            Unit(life, xSpeed,ySpeed, filepath, position, app, projectile_manager),
            m_player(player),
            direction("null"),
            lastShot(0),
            m_scoreHit(scoreHit),
            m_scoreExplosion(scoreExplosion),
            projectileSpeed(10),
            m_coefSpeed(coefSpeed),
            m_fireRate(firerate),
            savedTimerMove(0),
            m_imageManager(imageManager),
            m_type(type),
            m_moveMethod(moveMethod),
            m_moveValue(moveValue)
{

}

Boss::~Boss()
{

}

void Boss::recieveDamages(int dmg)
{
    m_life -= dmg;
    if(m_life < 0)
    {
        m_life = 0;
    }
}

void Boss::fireFocus()
{
    Vector2f distance;
    int indistinctness = rand() % 100 + 1;
    //On récupère les coordonnées du joueur
    playerPosition.x = m_player.getPosition(0);
    playerPosition.y = m_player.getPosition(1);
    distance.x = (playerPosition.x - m_position.x);
    distance.y = (playerPosition.y - m_position.y);
    int norm = sqrt(distance.x*distance.x + distance.y*distance.y);
    //On calcule la vitesse du projectile
    distance.x = ((distance.x+indistinctness)/norm)*projectileSpeed;
    distance.y = (distance.y/norm)*projectileSpeed;
    //La position de départ du projectile
    Vector2f positionProjectile = m_position;
    positionProjectile.x += (image->GetWidth()/2)-18;
    positionProjectile.y += image->GetHeight()-20;
    const string filepath = "images/projectile2.png";
    projectile = new Projectile(filepath, positionProjectile, Vector2f(distance.x, distance.y), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    //On le rajoute à la liste des projectiles gérée par le projectile manager.
    m_projectile_manager.addEnemyProjectile(projectile);
    lastShot = timer.getTime();
}

void Boss::fireCircle()
{
    //La position de départ du projectile
    Vector2f positionProjectile = m_position;
    positionProjectile.x += (image->GetWidth()/2)-20;
    positionProjectile.y += image->GetHeight()/2-20;
    const string filepath = "images/projectile2.png";
    projectile = new Projectile(filepath, positionProjectile, Vector2f(16, 0), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-16, 0), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(0, 16), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(0, -16), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(11, 11), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-11, 11), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(11, -11), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-11, -11), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);

    projectile = new Projectile(filepath, positionProjectile, Vector2f(-7, -14), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-5, -15), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(7, -14), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(5, -15), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(7, 14), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(5, 15), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-7, 14), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-5, 15), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);

    projectile = new Projectile(filepath, positionProjectile, Vector2f(-14, -7), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-15, -5), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(14, -7), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(15, -5), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(14, 7), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(15, 5), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-14, 7), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);
    projectile = new Projectile(filepath, positionProjectile, Vector2f(-15, 5), m_coefSpeed, m_imageManager);
    projectile->SetPosition(positionProjectile);
    m_projectile_manager.addEnemyProjectile(projectile);

    //On le rajoute à la liste des projectiles gérée par le projectile manager.
    lastShot = timer.getTime();
}

Sprite* Boss::getSprite()
{
    return &sprite;
}

IntRect Boss::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/4;
    boundingBox.Right = boundingBox.Left + image->GetWidth()-image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}

bool Boss::canFire()
{
    //Créé un interval de temps entre chaque tir
    if(timer.getTime() - lastShot > m_fireRate)
    {
        timer.reinitialize();
        return true;
    }
    else
        return false;
}

void Boss::startTimer()
{
    timer.start();
}

void Boss::pauseTimer()
{
    timer.pause();
}

int Boss::getPositionAxis(int axis)
{
    if(axis == 0)
        return m_position.x;
    else
        return m_position.y;
}


Vector2f Boss::getPosition()
{
    return m_position;
}

void Boss::setPosition(int axis, int value)
{
    if(axis == 1)
        m_position.x = value;
    else
        m_position.y = value;
}

Animated* Boss::getAnimation()
{
    return m_animated;
}

Animated* Boss::getAnimationExplosion()
{
    return m_animatedExplosion;
}

