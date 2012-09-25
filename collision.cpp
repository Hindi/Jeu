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

Collision::Collision(Vector2f windowSize, Player &player, Population &population, Projectile_manager &projectile_manager, Missile_manager &missile_manager, Drop_manager &drop_manager):
            m_player(player),
            m_population(population),
            m_windowSize(windowSize),
            m_projectile_manager(projectile_manager),
            m_missile_manager(missile_manager),
            m_drop_manager(drop_manager)
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
        list<Enemy*>::iterator li;
        for(li = m_population.getPopulation()->begin(); li!=m_population.getPopulation()->end();)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player.loseLive();
            }
            if(enemyRect.Top > 1500)
            {
               li = m_population.getPopulation()->erase(li);
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
    list<Projectile*>::iterator lit(m_projectile_manager.getPlayerProjectiles()->begin());
    list<Enemy*>::iterator li;
    list<Spawn*>::iterator spawnLi;
    //On check les ennemis
    for(; lit != m_projectile_manager.getPlayerProjectiles()->end(); lit++)
    {
        for(li = m_population.getPopulation()->begin(); li!=m_population.getPopulation()->end(); li++)
        {
            if(m_projectile_manager.getPlayerProjectiles()->size()>0)//Sans cette vérification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*lit)->getBoundingBox();
                projectilePosition.y = (*lit)->GetPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*lit)->getSprite().GetSize().y;
                enemyRect = (*li)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                {
                    (*li)->recieveDamages(m_player.getDamages());
                    m_player.addScore((*li)->getScoreHit());
                    (lit) = m_projectile_manager.getPlayerProjectiles()->erase(lit);
                }
            }
        }
    }

    //On check les spawn
    for(lit = m_projectile_manager.getPlayerProjectiles()->begin(); lit != m_projectile_manager.getPlayerProjectiles()->end(); lit++)
    {
        for(spawnLi = m_population.getSpawnPopulation()->begin(); spawnLi!=m_population.getSpawnPopulation()->end(); spawnLi++)
        {
            if(m_projectile_manager.getPlayerProjectiles()->size()>0)//Sans cette vérification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*lit)->getBoundingBox();
                projectilePosition.y = (*lit)->GetPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*lit)->getSprite().GetSize().y;
                enemyRect = (*spawnLi)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                {
                    (*spawnLi)->recieveDamages(m_player.getDamages());
                    (lit) = m_projectile_manager.getPlayerProjectiles()->erase(lit);
                }
            }
        }
    }

    //**************************
    // Collisions classe missile
    //**************************
    list<Missile*>::iterator litt(m_missile_manager.getMissile()->begin());
    for(; litt != m_missile_manager.getMissile()->end(); litt++)
    {
        //On check les ennemis
        for(li = m_population.getPopulation()->begin(); li!=m_population.getPopulation()->end(); li++)
        {
            if(m_missile_manager.getMissile()->size()>0)//Sans cette vérification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*litt)->getBoundingBox();
                projectilePosition.y = (*litt)->GetPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*litt)->getSprite().GetSize().y;
                enemyRect = (*li)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                {
                    (*li)->recieveDamages((*litt)->getDamage());
                    m_player.addScore((*li)->getScoreHit());
                    m_missile_manager.setPositionLibre((*litt)->getListPosition(),true);//La place est de nouveau libre pour créer un nouveau missile
                    (litt) = m_missile_manager.getMissile()->erase(litt);
                }
            }
        }

        //On check les spawn
        for(spawnLi = m_population.getSpawnPopulation()->begin(); spawnLi!=m_population.getSpawnPopulation()->end(); spawnLi++)
        {
            if(m_missile_manager.getMissile()->size()>0)//Sans cette vérification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*litt)->getBoundingBox();
                projectilePosition.y = (*litt)->GetPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*litt)->getSprite().GetSize().y;
                enemyRect = (*spawnLi)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                {
                    (*spawnLi)->recieveDamages((*litt)->getDamage());
                    m_missile_manager.setPositionLibre((*litt)->getListPosition(),true);//La place est de nouveau libre pour créer un nouveau missile
                    (litt) = m_missile_manager.getMissile()->erase(litt);
                }
            }
        }
    }
}

void Collision::dropCollision()
{
    IntRect playerRect = m_player.GetBoundingBox(), dropRect;
    list<Drop*>::iterator lit(m_drop_manager.getDrop()->begin());
    for(; lit!=m_drop_manager.getDrop()->end();)
    {
        dropRect = (*lit)->getBoundingBox();
        if((playerRect.Right > dropRect.Left && playerRect.Left < dropRect.Right && playerRect.Top > dropRect.Top && playerRect.Top < dropRect.Bottom) || dropRect.Bottom > 2000)
        {
            m_player.addScore(100);
            lit = m_drop_manager.getDrop()->erase(lit);
        }
        else
        {
            lit++;
        }

    }
}
