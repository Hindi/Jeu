#include "collision.h"

using namespace std;
using namespace sf;

bool checkCollision(const IntRect & a, const IntRect & b)
{
    if (a.Bottom <= b.Top)
        return false;
    if (a.Top >= b.Bottom)
        return false;
    if (a.Right <= b.Left)
        return false;
    if (a.Left >= b.Right)
        return false;

    return true;
}

Collision::Collision(Vector2f windowSize, Player &player, Population &population): m_windowSize(windowSize), m_player(player), m_population(population)
{

}

Collision::~Collision()
{

}

void Collision::manageCollisionsX()
{
    IntRect playerRect = m_player.GetBoundingBox(), enemyRect;
    if(playerRect.Left < 0)
    {
        m_player.setPosition(1, 0);
    }
    else if(playerRect.Right > m_windowSize.x )
    {
        m_player.setPosition(1, m_windowSize.x-(-playerRect.Left+playerRect.Right));
    }

    if(!m_player.getLostlife())
    {
        list<Enemy*>::iterator li;
        for(li = m_population.getPopulation()->begin(); li!=m_population.getPopulation()->end(); li++)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+50 && playerRect.Left < enemyRect.Right-50 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom+100)
            {
                m_player.loseLive();
            }
        }
    }

}

void Collision::manageCollisionsY()
{
    IntRect playerRect = m_player.GetBoundingBox(), enemyRect;
    if(playerRect.Top < 0)
    {
        m_player.setPosition(2, 0);
    }
    else if(playerRect.Bottom > m_windowSize.y)
    {
        m_player.setPosition(2, (m_windowSize.y-(-playerRect.Top+playerRect.Bottom)));
    }

    if(!m_player.getLostlife())
    {
        list<Enemy*>::iterator li;
    for(li = m_population.getPopulation()->begin(); li!=m_population.getPopulation()->end(); li++)
    {
        enemyRect = (*li)->getBoundingBox();
        if(playerRect.Right > enemyRect.Left+50 && playerRect.Left < enemyRect.Right-50 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom+100)
        {
            m_player.loseLive();
        }
    }
    }

}

void Collision::manageProjectileCollision()
{
    IntRect projectileRect, enemyRect;
    Vector2f projectilePosition;
    list<Projectile*>::iterator lit;
    list<Enemy*>::iterator li;
    for(lit = m_player.getProjectiles()->begin(); lit != m_player.getProjectiles()->end(); lit++)
    {
        for(li = m_population.getPopulation()->begin(); li!=m_population.getPopulation()->end(); li++)
        {
            projectileRect = (*lit)->getBoundingBox();
            projectilePosition.y = (*lit)->GetPosition().y;
            projectileRect.Top  = projectilePosition.y;
            projectileRect.Bottom = projectileRect.Top+(*lit)->getSprite().GetSize().y;
            enemyRect = (*li)->getBoundingBox();
            if(projectileRect.Right > enemyRect.Left+15 && projectileRect.Left < enemyRect.Right-15 && projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom+225)
            {
                (*li)->recieveDamages(5);
                m_player.addScore((*li)->getScore());
            }
        }
    }

}
