#include "enemy.h"

using namespace std;
using namespace sf;

Enemy::Enemy(int life, int score, int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app):Unit(1, xSpeed, ySpeed, filepath, position, app), lastShot(0), m_score(score)
{
    timer.start();
    animation->initialize(m_position.x, m_position.y, 1, 1);

}

Enemy::~Enemy()
{

}

Sprite* Enemy::getSprite()
{
    return &sprite;
}

int Enemy::getScore()
{
    return m_score;
}

IntRect Enemy::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = (int)m_position.x;
    boundingBox.Right = boundingBox.Left + animation->getFrameWidth();
    boundingBox.Top = (int)m_position.y;
    boundingBox.Bottom = boundingBox.Top + animation->getFrameHeight();

    return boundingBox;
}

void Enemy::recieveDamages(int dmg)
{
    m_life -= dmg;
    if(m_life < 0)
    {
        m_life = 0;
    }
}

bool Enemy::isDead()
{
    if(m_life == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Enemy::moveUp()
{
    animation->setActive(true);
    m_position.y -= m_ySpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 0;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Enemy::moveDown()
{
    animation->setActive(true);
    m_position.y += m_ySpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 0;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Enemy::moveLeft()
{
    animation->setActive(true);
    m_position.x -= m_xSpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 1;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Enemy::moveRight()
{
    animation->setActive(true);
    m_position.x += m_xSpeed * m_app.GetFrameTime() * coefSpeed;
    currentFrameY = 2;
    animation->setPosition(1, m_position.x);
    animation->setPosition(2, m_position.y);
    animation->setCurrentFrame(2, currentFrameY);
    animation->update(m_app);
}

void Enemy::draw()
{
    animation->setActive(true);
    animation->update(m_app);
    animation->draw(m_app);
}

int Enemy::getPosition(int axis)
{
    if(axis == 0)
        return m_position.x;
    else
        return m_position.y;
}

void Enemy::setPosition(int axis, int value)
{
    if(axis == 1)
        m_position.x = value;
    else
        m_position.y = value;
}
