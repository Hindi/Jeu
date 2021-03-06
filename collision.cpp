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

Collision::Collision(Vector2f windowSize, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            m_player(player),
            m_player2(player2),
            m_windowSize(windowSize)

{
    clingBuffer = sound_manager::getInstance()->getBuffer("son/cling.ogg");
    clingSound.SetBuffer(clingBuffer);
    clingSound.SetLoop(false);
    clingSound.SetPitch(1.f);
    clingSound.SetVolume(50.f);
}

Collision::~Collision()
{

}

void Collision::manageCollisionsX()
{
    IntRect playerRect = m_player->GetBoundingBox(), enemyRect;
    if(playerRect.Left < 0)
    {
        m_player->setPosition(1, 0);
    }
    else if(playerRect.Right > m_windowSize.x )
    {
        m_player->setPosition(1, m_windowSize.x-(-playerRect.Left+playerRect.Right));
    }

    if(!m_player->getLostlife())
    {
        list<tr1::shared_ptr<Enemy> >::iterator li(Population::getInstance()->getPopulation()->begin());
        for(; li!=Population::getInstance()->getPopulation()->end(); li++)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player->loseLive();
            }
        }
    }

    this->dropCollision();
}

void Collision::manageCollisionsX2()
{
    IntRect playerRect = m_player2->GetBoundingBox(), enemyRect;
    if(playerRect.Left < 0)
    {
        m_player2->setPosition(1, 0);
    }
    else if(playerRect.Right > m_windowSize.x )
    {
        m_player2->setPosition(1, m_windowSize.x-(-playerRect.Left+playerRect.Right));
    }

    if(!m_player2->getLostlife())
    {
        list<tr1::shared_ptr<Enemy> >::iterator li(Population::getInstance()->getPopulation()->begin());
        for(; li!=Population::getInstance()->getPopulation()->end(); li++)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player2->loseLive();
            }
        }
    }

    this->dropCollision();
}

void Collision::manageCollisionsY()
{
    IntRect playerRect = m_player->GetBoundingBox(), enemyRect;
    if(playerRect.Top < 0)
    {
        m_player->setPosition(2, 0);
    }
    else if(playerRect.Bottom > m_windowSize.y)
    {
        m_player->setPosition(2, (m_windowSize.y-(-playerRect.Top+playerRect.Bottom)));
    }


    if(!m_player->getLostlife())
    {
        list<tr1::shared_ptr<Enemy> >::iterator li;
        for(li = Population::getInstance()->getPopulation()->begin(); li!=Population::getInstance()->getPopulation()->end();)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player->loseLive();
            }
            if(enemyRect.Top > 800)
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

void Collision::manageCollisionsY2()
{
    IntRect playerRect = m_player2->GetBoundingBox(), enemyRect;
    if(playerRect.Top < 0)
    {
        m_player2->setPosition(2, 0);
    }
    else if(playerRect.Bottom > m_windowSize.y)
    {
        m_player2->setPosition(2, (m_windowSize.y-(-playerRect.Top+playerRect.Bottom)));
    }


    if(!m_player2->getLostlife())
    {
        list<tr1::shared_ptr<Enemy> >::iterator li;
        for(li = Population::getInstance()->getPopulation()->begin(); li!=Population::getInstance()->getPopulation()->end();)
        {
            enemyRect = (*li)->getBoundingBox();
            if(playerRect.Right > enemyRect.Left+20 && playerRect.Left < enemyRect.Right-20 && playerRect.Top > enemyRect.Top && playerRect.Top < enemyRect.Bottom)
            {
                m_player2->loseLive();
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
    IntRect projectileRect, enemyRect, bossWeakRecy, player1Rect, player2Rect;
    Vector2f projectilePosition;
    list<std::tr1::shared_ptr<Projectile> >* playerProjectile = Projectile_manager::getInstance()->getPlayerProjectiles();
    list<std::tr1::shared_ptr<Projectile> >* enemyProjectile = Projectile_manager::getInstance()->getEnemyProjectiles();
    list<tr1::shared_ptr<Enemy> >::iterator li(Population::getInstance()->getPopulation()->begin());
    //Si il y a des projectiles en jeu
    int i(0);

    if(!playerProjectile->empty())
    {
        list<std::tr1::shared_ptr<Projectile> >::iterator lit(playerProjectile->begin());
        //Pour chaque ennemi
        for(; li!=Population::getInstance()->getPopulation()->end(); li++)
        {
            //Pour chaque projectile
            while(lit != playerProjectile->end())
            {
                //On r�cup�re les coordonn�es du carr� occup� par le projectile � l'�cran
                projectileRect = (*lit)->getBoundingBox();
                //On r�cup�re les coordonn�es du carr� occup� par l'ennemi � l'�cran
                enemyRect = (*li)->getBoundingBox();
                //On regarde si ils se superposent
                if(strcmp((*li)->getType(), "boss")==0)
                    {
                        bossWeakRecy = (*li)->getWeakBox();
                        if(projectileRect.Top > bossWeakRecy.Top && projectileRect.Top < bossWeakRecy.Bottom && projectileRect.Left > bossWeakRecy.Left && projectileRect.Right < bossWeakRecy.Right)
                        {
                            //Si oui l'ennemis perd de la vie
                            (*li)->recieveDamages(m_player->getDamages());
                            //Et le score des deux joueurs augmente
                            m_player->addScore((*li)->getScoreHit()/2);
                            m_player2->addScore((*li)->getScoreHit()/2);
                            //On supprime le projectile
                            (lit) = playerProjectile->erase(lit);

                            if(!(*li)->isDead())
                            {
                                Vector2f position;
                                position.x = (*li)->getPositionAxis(0);
                                position.y = (*li)->getPositionAxis(1);
                                int currentFrame = (*li)->getAnimation()->GetCurrentFrame();
                                Anim *m_anim = (*li)->getAnimation()->GetAnim();
                                Image *currentImage = (*m_anim)[currentFrame].Image;
                                position.x += currentImage->GetWidth();
                                Score_manager::getInstance()->addScore((*li)->getScoreHit()/2, position);
                            }
                        }
                        else if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                        {
                            //On supprime le projectile
                            (lit) = playerProjectile->erase(lit);
                        }
                        else
                            lit++;
                    }
                    else
                    {
                        if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left && projectileRect.Left < enemyRect.Right)
                        {

                            //Si oui l'ennemis perd de la vie
                            (*li)->recieveDamages(m_player->getDamages());
                            //Et le score des deux joueurs augmente
                            m_player->addScore((*li)->getScoreHit()/2);
                            m_player2->addScore((*li)->getScoreHit()/2);
                            //On supprime le projectile
                            (lit) = playerProjectile->erase(lit);

                            if(!(*li)->isDead())
                            {
                                Vector2f position;
                                position.x = (*li)->getPositionAxis(0);
                                position.y = (*li)->getPositionAxis(1);
                                int currentFrame = (*li)->getAnimation()->GetCurrentFrame();
                                Anim *m_anim = (*li)->getAnimation()->GetAnim();
                                Image *currentImage = (*m_anim)[currentFrame].Image;
                                position.x += currentImage->GetWidth();
                                Score_manager::getInstance()->addScore((*li)->getScoreHit()/2, position);
                            }
                        }
                        else
                            lit++;
                    }
            }
            lit = playerProjectile->begin();
        }
    }

    //**************************
    // Collisions classe missile
    //**************************
    list<std::tr1::shared_ptr<Missile> >::iterator litt(Missile_manager::getInstance()->getMissile()->begin());
    //On check les ennemis
    for(li = Population::getInstance()->getPopulation()->begin(); li!=Population::getInstance()->getPopulation()->end(); li++)
    {
        while(litt != Missile_manager::getInstance()->getMissile()->end())
        {
            if(Missile_manager::getInstance()->getMissile()->size()>0)//Sans cette v�rification, la destruction d'un projectile dans une liste de taille = 1 entraine un crash
            {
                projectileRect = (*litt)->getBoundingBox();
                projectilePosition.y = (*litt)->GetPosition().y;
                projectileRect.Top  = projectilePosition.y;
                projectileRect.Bottom = projectileRect.Top+(*litt)->getSprite().GetSize().y;
                enemyRect = (*li)->getBoundingBox();
                if(projectileRect.Top > enemyRect.Top && projectileRect.Top < enemyRect.Bottom && projectileRect.Right > enemyRect.Left+5 && projectileRect.Left < enemyRect.Right-5)
                {
                    (*li)->recieveDamages((*litt)->getDamage());
                    m_player->addScore((*li)->getScoreHit());
                    Missile_manager::getInstance()->setPositionLibre((*litt)->getListPosition(),true);//La place est de nouveau libre pour cr�er un nouveau missile
                    (litt) = Missile_manager::getInstance()->getMissile()->erase(litt);
                }
                else
                    litt++;
            }
        }
        litt = Missile_manager::getInstance()->getMissile()->begin();
    }

    if(Projectile_manager::getInstance()->haveEnemyProjectilesInProgress())
    {
        list<std::tr1::shared_ptr<Projectile> >::iterator lit(enemyProjectile->begin());
        while(lit != enemyProjectile->end())
        {
            projectileRect = (*lit)->getBoundingBox();
            player1Rect = m_player->GetBoundingBox();
            player2Rect = m_player2->GetBoundingBox();

            if(projectileRect.Bottom > player1Rect.Top+40 && projectileRect.Top < player1Rect.Bottom-40 && projectileRect.Right > player1Rect.Left+70 && projectileRect.Left < player1Rect.Right-70)
            {
                //Si oui l'ennemis perd de la vie
                m_player->loseLive();

                //On supprime le projectile
                (lit) = enemyProjectile->erase(lit);
            }
            else if(projectileRect.Bottom > player2Rect.Top+40 && projectileRect.Top < player2Rect.Bottom-40 && projectileRect.Right > player2Rect.Left+70 && projectileRect.Left < player2Rect.Right-70)
            {
                //Si oui l'ennemis perd de la vie
                m_player2->loseLive();

                //On supprime le projectile
                (lit) = enemyProjectile->erase(lit);
            }
            else
                lit++;
        }
    }

}

void Collision::dropCollision()
{
    IntRect playerRect = m_player->GetBoundingBox(), dropRect;
    list<std::tr1::shared_ptr<Drop> >::iterator lit(Drop_manager::getInstance()->getDrop()->begin());
    for(; lit!=Drop_manager::getInstance()->getDrop()->end();)
    {
        dropRect = (*lit)->getBoundingBox();
        if((playerRect.Right > dropRect.Left && playerRect.Left < dropRect.Right && playerRect.Top > dropRect.Top && playerRect.Top < dropRect.Bottom) || dropRect.Bottom > 2000)
        {
            m_player->addScore(100);
            lit = Drop_manager::getInstance()->getDrop()->erase(lit);
            clingSound.Play();
        }
        else
        {
            lit++;
        }
    }

    playerRect = m_player2->GetBoundingBox(), dropRect;
    list<std::tr1::shared_ptr<Drop> >::iterator li(Drop_manager::getInstance()->getDrop()->begin());
    for(; li!=Drop_manager::getInstance()->getDrop()->end();)
    {
        dropRect = (*li)->getBoundingBox();
        if((playerRect.Right > dropRect.Left && playerRect.Left < dropRect.Right && playerRect.Top > dropRect.Top && playerRect.Top < dropRect.Bottom) || dropRect.Bottom > 2000)
        {
            m_player2->addScore(100);
            li = Drop_manager::getInstance()->getDrop()->erase(li);
            clingSound.Play();
        }
        else
        {
            li++;
        }

    }
}
