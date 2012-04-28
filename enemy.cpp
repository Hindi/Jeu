#include "enemy.h"

using namespace std;
using namespace sf;

Enemy::Enemy(int life, int score, int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app, IntRect subRect):Unit(1, xSpeed, ySpeed, filepath, position, app, subRect), lastShot(0), m_score(score)
{
    timer.start();
}

Enemy::~Enemy()
{

}

Sprite* Enemy::getSprite()
{
    return &sprite;
}

IntRect Enemy::getBoundingBox() const
{
    IntRect boundingBox;
    boundingBox.Left = (int)sprite.GetPosition().x;
    boundingBox.Right = boundingBox.Left + sprite.GetSize().x;
    boundingBox.Top = (int)sprite.GetPosition().y;
    boundingBox.Bottom = boundingBox.Top + sprite.GetSize().y;

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

int Enemy::getScore()
{
    return m_score;
}
