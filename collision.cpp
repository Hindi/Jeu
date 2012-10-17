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

Collision::Collision(Vector2f windowSize, Player &player):
            m_player(player),
            m_windowSize(windowSize)
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
        list<tr1::shared_ptr<Enemy> >::iterator li(Population::getInstance()->getPopulation()->begin());
        for(; li!=Population::getInstance()->getPopulation()->end(); li++)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player.loseLive();
            }
        }
    }

    this->dropCollision();

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
        list<tr1::shared_ptr<Enemy> >::iterator li;
        for(li = Population::getInstance()->getPopulation()->begin(); li!=Population::getInstance()->getPopulation()->end();)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player.loseLive();
            }
            if(enemyRect.Top > 1500)
            {
               li = Population::getInstance()->getPopulation()->erase(li);
            }
            else
            {
                li++;
            }
        }
    }

    this->dropCollision();
}

void Collision::manageProjectileCollision()
{
    //*****************************
    // Collisions classe projectile
    //*****************************
    IntRect projectileRect, enemyRect;
    Vector2f projectilePosition;
    list<std::tr1::shared_ptr<Projectile> >::iterator lit(Projectile_manager::getInstance()->getPlayerProjectiles()->begin());
    list<tr1::shared_ptr<Enemy> >::iterator li;
    list<Spawn*>::iterator spawnLi;
    //On check les ennemis
    for(; lit != Projectile_manager::getInstance()->getPlayerProjectiles()->end(); lit++)
    {
        for(li = Population::getInstance()->getPopulation()->begin(); li!=Population::getInstance()->getPopulation()->end(); li++)
        {
            if(Projectile_manager::getInstance()->getPlayerProjectiles()->size()>0)//Sans cette vérification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*lit)->getBoundingBox();
                projectilePosition.y = (*lit)->getPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*lit)->getSprite().GetSize().y;
                enemyRect = (*li)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                {
                    (*li)->recieveDamages(m_player.getDamages());
                    m_player.addScore((*li)->getScoreHit());
                    (lit) = Projectile_manager::getInstance()->getPlayerProjectiles()->erase(lit);
                }
            }
        }
    }

    //**************************
    // Collisions classe missile
    //**************************
    list<std::tr1::shared_ptr<Missile> >::iterator litt(Missile_manager::getInstance()->getMissile()->begin());
    for(; litt != Missile_manager::getInstance()->getMissile()->end(); litt++)
    {
        //On check les ennemis
        for(li = Population::getInstance()->getPopulation()->begin(); li!=Population::getInstance()->getPopulation()->end(); li++)
        {
            if(Missile_manager::getInstance()->getMissile()->size()>0)//Sans cette vérification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*litt)->getBoundingBox();
                projectilePosition.y = (*litt)->GetPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*litt)->getSprite().GetSize().y;
                enemyRect = (*li)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left+5 && projectileRect.Left < enemyRect.Right-5)
                {
                    (*li)->recieveDamages((*litt)->getDamage());
                    m_player.addScore((*li)->getScoreHit());
                    Missile_manager::getInstance()->setPositionLibre((*litt)->getListPosition(),true);//La place est de nouveau libre pour créer un nouveau missile
                    (litt) = Missile_manager::getInstance()->getMissile()->erase(litt);
                }
            }
        }
    }
}

void Collision::dropCollision()
{
    IntRect playerRect = m_player.GetBoundingBox(), dropRect;
    list<std::tr1::shared_ptr<Drop> >::iterator lit(Drop_manager::getInstance()->getDrop()->begin());
    for(; lit!=Drop_manager::getInstance()->getDrop()->end();)
    {
        dropRect = (*lit)->getBoundingBox();
        if((playerRect.Right > dropRect.Left && playerRect.Left < dropRect.Right && playerRect.Top > dropRect.Top && playerRect.Top < dropRect.Bottom) || dropRect.Bottom > 2000)
        {
            m_player.addScore(100);
            lit = Drop_manager::getInstance()->getDrop()->erase(lit);
        }
        else
        {
            lit++;
        }

    }
}
