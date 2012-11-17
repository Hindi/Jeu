#include "ship.h"

using namespace std;
using namespace sf;

Ship::Ship(Vector2f position, const std::string &move, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Enemy(10, 10, 100, 5, 5, "images/enemy.png", position, "ship", move, 1, m_coefSpeed, 1, false, player, player2, false)
{

}

Ship::~Ship()
{

}

void Ship::fire()
{
    Vector2f distance1, distance2, position1, position2;
    int indistinctness = rand() % 100 + 1;
    int norm;
    //On récupère les positions des deux joueurs
    position1 = player->getPosition();
    position2 = player2->getPosition();

    //On calcule leur deux normes
    distance1.x = (position1.x - m_position.x);
    distance1.y = (position1.y - m_position.y);
    int norm1 = sqrt(distance1.x*distance1.x + distance1.y*distance1.y);

    distance2.x = (position2.x - m_position.x);
    distance2.y = (position2.y - m_position.y);
    int norm2 = sqrt(distance2.x*distance2.x + distance2.y*distance2.y);

    if(norm1 > norm2)
    {
        distance1 = distance2;
        norm = norm2;
    }
    else
        norm = norm1;

    //On calcule la vitesse du projectile
    distance1.x = ((distance1.x+indistinctness)/norm)*projectileSpeed;
    distance1.y = ((distance1.y+indistinctness)/norm)*projectileSpeed;

    //La position de départ du projectile
    Vector2f positionProjectile(m_position);
    positionProjectile.x += (image->GetWidth()/2)-60;
    positionProjectile.y += image->GetHeight()-20;
    const string filepath = "images/projectile4.png";
    std::tr1::shared_ptr<Projectile> projectile(new Projectile(filepath, positionProjectile, distance1, m_coefSpeed, true));
    projectile->setPosition(positionProjectile);

    //On le rajoute à la liste des projectiles gérée par le projectile manager.
    Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    lastShot = timer.getTime();
}
