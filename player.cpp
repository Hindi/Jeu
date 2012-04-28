#include "player.h"

using namespace std;
using namespace sf;

Player::Player(int life, int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app, IntRect subRect):Unit(1, xSpeed, ySpeed, filepath, position, app, subRect), max_lives(3), lastShot(0), fireRate(0.1), m_lives(4), m_score(0), lostLife(false)
{
    timer.start();
}

Player::~Player()
{
    list<Projectile*>::const_iterator lit(m_projectiles.begin());
    for(; lit!=m_projectiles.end(); lit++)
    {
        delete *lit;
    }
}


Sprite* Player::getSprite()
{
    //Retourne la référence de sprite
    return &sprite;
}

int Player::getLives()
{
    //Retourne le nombre de vies restantes
    return m_lives;
}

IntRect Player::GetBoundingBox() const
{
    //Récupère le rectangle de collision pour le joueur
    IntRect boundingBox;
    boundingBox.Left = (int)sprite.GetPosition().x;
    boundingBox.Right = boundingBox.Left + sprite.GetSize().x;
    boundingBox.Top = (int)sprite.GetPosition().y;
    boundingBox.Bottom = boundingBox.Top + sprite.GetSize().y;

    return boundingBox;
}

void Player::fire()
{
    //Créé les projectiles
    if(canFire(lastShot, timer, fireRate))
    {
        this->refreshPosition();
        Vector2f positionProjectile = m_position;
        positionProjectile.x += 39;
        positionProjectile.y -= 113;
        const string filepath = "images/projectile.png";

        projectile = new Projectile(filepath, positionProjectile, 20);
        m_projectiles.push_back(projectile);
        lastShot = timer.getTime();
    }
}

list<Projectile*>* Player::getProjectiles()
{
    //Retourne la référence de la liste des projectiles
    return &m_projectiles;
}

bool Player::HaveProjectilesInProgress()
{
    //Vérifie si des projectiles sont en cours de déplacement
    if(m_projectiles.size() > 0)
        return true;
    else
        return false;
}

void Player::moveProjectile()
{
    //Déplace les projectiles et les détruit s'ils sortent de l'écran
    double elapsedTime = m_app.GetFrameTime();
    list<Projectile*>::iterator lit(m_projectiles.begin());
    Vector2f speed(0,-((*lit)->getSpeed())*elapsedTime*(*lit)->getCoefSpeed());
    for(; lit!=m_projectiles.end(); )
    {
        (*lit)->Move(speed);
        if((*lit)->GetPosition().y+1000  < 0)
        {
            lit = m_projectiles.erase(lit);
        }
        else
        {
            lit++;
        }
    }
}

void Player::drawProjectile()
{
    //Dessine les projectiles pour qu'ils soient affichés à l'écran
    list<Projectile*>::const_iterator lit(m_projectiles.begin());
    for(; lit!=m_projectiles.end(); lit++)
    {
        m_app.Draw(**lit);
    }
}


bool canFire(float lastShot, Timer &timer, float const fireRate)
{
    //Créé un interval de temps entre chaque tir
    if(timer.getTime() - lastShot > fireRate)
    {
        timer.reinitialize();
        return true;
    }
    else
        return false;
}

void Player::addScore(int score)
{
    m_score += score;
}

double Player::getScore()
{
    return m_score;
}

void Player::loseLive()
{
    Vector2f position(500, 1000);
    sprite.SetPosition(position);
    m_lives -= 1;
    lostLife = true;
}

bool Player::getLostlife()
{
    return lostLife;
}

void Player::resetLostLife()
{
    lostLife = false;
}

void Player::refreshPosition()
{
    m_position = sprite.GetPosition();
}
