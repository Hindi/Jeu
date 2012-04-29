#include "player.h"

using namespace std;
using namespace sf;

Player::Player(int life, int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app):Unit(1, xSpeed, ySpeed, filepath, position, app), max_lives(3), lastShot(0), fireRate(0.1), m_lives(4), m_score(0), lostLife(false)
{
    timer.start();
    currentFrameX = currentFrameY = 0;
    animation->initialize(m_position.x, m_position.y, 5, 3);
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

IntRect Player::GetBoundingBox()
{
    //Récupère le rectangle de collision pour le joueur
    IntRect boundingBox;
    boundingBox.Left = (int)m_position.x;
    boundingBox.Right = boundingBox.Left + animation->getFrameWidth();
    boundingBox.Top = (int)m_position.y;
    boundingBox.Bottom = boundingBox.Top + animation->getFrameHeight();

    return boundingBox;
}

void Player::fire()
{
    //Créé les projectiles
    if(canFire(lastShot, timer, fireRate))
    {
        Vector2f positionProjectile = m_position;
        positionProjectile.x += 39;
        positionProjectile.y -= 30;
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
void Player::loadContent()
{
    if(image->LoadFromFile("images/player.png"))
    {
        animation->setImage(*image);
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
    m_position = position;
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


void Player::moveUp()
{
    animation->setActive(true);
    m_position.y -= m_ySpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 0;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Player::moveDown()
{
    animation->setActive(true);
    m_position.y += m_ySpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 0;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Player::moveLeft()
{
    animation->setActive(true);
    m_position.x -= m_xSpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 1;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Player::moveRight()
{
    animation->setActive(true);
    m_position.x += m_xSpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 2;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Player::dontMove()
{
    animation->setActive(true);
    currentFrameY = 0;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Player::draw()
{
    animation->draw(m_app);
}


int Player::getPosition(int axis)
{
    if(axis == 0)
        return m_position.x;
    else
        return m_position.y;
}

void Player::setPosition(int axis, int value)
{
    if(axis == 1)
        m_position.x = value;
    else
        m_position.y = value;
}
