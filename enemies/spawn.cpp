#include "spawn.h"

using namespace std;
using namespace sf;

Spawn::Spawn(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, char* type, int moveValue,
              const int coefSpeed, const int firerate, Player &player):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, "don't move", moveValue,
              coefSpeed, firerate, false, player),
            moveRate(1)
{
    image = new Image();
    *image = image_manager::getInstance()->getImage("images/Etoile1.png");
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated = new Animated();
    m_animated->SetAnim(&m_anim);
    m_animated->Pause();
    m_animated->SetLoop(true);
    m_animated->SetFrameTime(0.2f);
    m_animated->SetPosition(m_position.x, m_position.y);

    timerMove.start();
    timerFire.start();
}

Spawn::~Spawn()
{

}


void Spawn::fire()
{
    if(timerFire.getTime() - lastShot > m_fireRate)
    {
        lastShot = timerFire.getTime();
        Vector2f distance;
        Vector2f playerPosition;
        int indistinctness = rand() % 100 + 1;
        //On r�cup�re les coordonn�es du joueur
        playerPosition.x = player.getPosition(0);
        playerPosition.y = player.getPosition(1);
        distance.x = (playerPosition.x - m_position.x);
        distance.y = (playerPosition.y - m_position.y);
        int norm = sqrt(distance.x*distance.x + distance.y*distance.y);
        //On calcule la vitesse du projectile
        distance.x = ((distance.x+indistinctness)/norm)*projectileSpeed;
        distance.y = (distance.y/norm)*projectileSpeed;
        //La position de d�part du projectile
        Vector2f positionProjectile = m_position;
        positionProjectile.x += (image->GetWidth()/2)-18;
        positionProjectile.y += image->GetHeight()-20;
        const string filepath = "images/projectile2.png";
        projectile = new Projectile(filepath, positionProjectile, Vector2f(distance.x, distance.y), coefSpeed);
        projectile->setPosition(positionProjectile);
        //On le rajoute � la liste des projectiles g�r�e par le projectile manager.
        Projectile_manager::getInstance()->addEnemyProjectile(projectile);
    }
}

void Spawn::move()
{
    Vector2f speed;
    if(timerMove.getTime() - lastMove > moveRate)
    {
        m_angleMove = rand() % 360 + 1;
        lastMove = timerMove.getTime();
    }
    speed.x = app.GetFrameTime() * m_xSpeed * m_coefSpeed * cos(m_angleMove);
    speed.y = app.GetFrameTime() * m_ySpeed * m_coefSpeed * sin(m_angleMove);
    m_position += speed;
    m_animated->SetPosition(m_position);
}

void Spawn::draw()
{
    app.Draw(*m_animated);
}

IntRect Spawn::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x + image->GetWidth()/4;
    boundingBox.Right = boundingBox.Left + image->GetWidth()-image->GetWidth()/2;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}

Vector2f Spawn::getPosition()
{
    return m_position;
}
