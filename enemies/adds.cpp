#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, Vector2f speed, const string &filepath, Vector2f position, RenderWindow &app, Projectile_manager projectile_manager,
            Player &player, image_manager &imageManager, int maxLife):
            Unit(life, speed.x,speed.y, position, app, projectile_manager),
            m_scoreHit(20),
            m_scoreExplosion(500),
            projectileSpeed(10),
            m_coefSpeed(50),
            m_fireRate(1),
            m_player(player),
            m_imageManager(imageManager),
            m_maxLife(maxLife)
{

}

Adds::~Adds()
{

}

void Adds::recieveDamages(int dmg)
{
    m_life -= dmg;
    if(m_life < 0)
        m_life = 0;
    else if(m_life > m_maxLife)
        m_life = m_maxLife;
}


bool Adds::canFire()
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

void Adds::fireFocus()
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

void Adds::fireCircle()
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

Sprite* Adds::getSprite()
{
    return &sprite;
}


list<Projectile*> Adds::getProjectiles()
{
    return m_projectiles;
}
