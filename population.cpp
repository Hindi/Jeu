#include "population.h"

using namespace std;
using namespace sf;

Population *Population::_singleton= NULL;

Population::Population()
{
    m_coefSpeed = 10;
    player = NULL;
    Population* _singleton= NULL;
}


Population::~Population()
{
    if(this->haveEnnemyInProgress())
    {
        list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();)
        {
            delete *lit;
        }
    }
    m_enemies.clear();
}

void Population::drawPopulation()
{
    if(this->haveEnnemyInProgress())
    {
        list<Enemy*>::const_iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end(); lit++)//Si des ennemis sont en vie
        {
            (*lit)->draw();//On les dessine
        }
    }
    Projectile_manager::getInstance()->drawProjectile();//On les dessine

}

list<Enemy*>* Population::getPopulation()
{
    //Retourne la liste des ennemis
    return &m_enemies;
}

void Population::checkPopulation()
{
    if(this->haveEnnemyInProgress())
    {
        //On check les ennemis
        list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();)
        {
            if((*lit)->isDead())
            {
                this->explode(*lit);
                lit = m_enemies.erase(lit);
            }
            else
            {
                (*lit)->move();
                this->spawn((*lit));
                if((*lit)->canFire())
                {
                    if(strcmp((*lit)->getType(), "ship") == 0)
                        (*lit)->fireFocus();
                    else if(strcmp((*lit)->getType(), "flyingSaucer") == 0)
                        (*lit)->fireCircle();
                }
                lit++;
            }
        }
    }

    Projectile_manager::getInstance()->moveProjectile();


    if(freezed == true && timerFreeze.getTime() > 2)
    {
        this->unfreeze();
        timerFreeze.pause();
        timerFreeze.reinitialize();
        freezed = false;
    }

}

void Population::explode(Enemy *enemy)
{
    m_deadEnemies.push_back(enemy);

    Vector2f position;
    int score;
    score = enemy->getScoreExplosion();
    position.x = enemy->getPositionAxis(0);
    position.y = enemy->getPositionAxis(1);
    Drop_manager::getInstance()->createDrop(score, position);
    int currentFrame = enemy->getAnimation()->GetCurrentFrame();
    Anim *m_anim = enemy->getAnimation()->GetAnim();
    Image *currentImage = (*m_anim)[currentFrame].Image;
    position.x += currentImage->GetWidth();
    Score_manager::getInstance()->addScore(score, position);
}

void Population::manageExplosion()
{
    if(!m_deadEnemies.empty())
    {
        short currentFrame;
        list<Enemy*>::iterator lit(m_deadEnemies.begin());
        for(; lit!=m_deadEnemies.end();lit++)
        {
            //Si l'animation est en pause
            if((*lit)->getAnimationExplosion()->IsPaused())
                (*lit)->getAnimationExplosion()->Play();//On relance l'animation
            //On r�cup�re le num�ro de l'image qui est affich�e
            currentFrame = (*lit)->getAnimationExplosion()->GetCurrentFrame();

            //On positionne l'animation sur l'ennemi qui a explose
            (*lit)->getAnimationExplosion()->SetPosition((*lit)->getPositionAxis(0)-((*lit)->getExploWidth()/2), (*lit)->getPositionAxis(2)-((*lit)->getExploHeight()/2)+30);
             //On dessine l'explosion
            (*lit)->drawExplosion();
            //Si l'image actuelle correspond � la derni�re image de l'animation
            if(currentFrame == (*lit)->getAnimationExplosion()->GetAnim()->Size()-1)
            {
                lit = m_deadEnemies.erase(lit);//On d�truit l'objet ennemi
            }
        }
    }
}

bool Population::haveEnnemyInProgress()
{
    if(m_enemies.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Population::stop()
{
    list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();lit++)
        {
            (*lit)->pauseTimer();
        }
}

void Population::unStop()
{
    list<Enemy*>::iterator lit(m_enemies.begin());
    for(; lit!=m_enemies.end();lit++)
            {
                (*lit)->startTimer();
            }
}

void Population::createShip(Vector2f position, char* move, bool spawner)
{
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    m_enemies.push_back(new Enemy(10, 10, 100, 5, 5, "images/enemy.png", position, "ship", move, 1, 40, 1, spawner, *player));
}

void Population::createFlyingSaucer(Vector2f position, char* move, bool spawner)
{
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    m_enemies.push_back(new Enemy(30, 10, 500, 0, 0, "images/enemy2.png", position, "flyingSaucer", move, 1, 20, 2, spawner, *player));
}

void Population::createBoss(Vector2f position, char* move, char* name)
{
    m_enemies.push_back(new Boss(500, 10, 10000, 5, 5, name, position, "boss", move, 1, 20, 2, name, *player));
}

void Population::manage()
{
    this->checkPopulation();
    this->manageExplosion();
    this->drawPopulation();
}

bool Population::haveSpawnInProgress()
{
    if(m_spawns.empty())
        return false;
    else
        return true;
}

void Population::spawn(Enemy *enemy)
{
    if(enemy->isSpawner() && (enemy->getSpawnTime() - enemy->getLastSpawnTime() > enemy->getSpawnRate()))
    {
        Vector2f position = enemy->getPosition();
        m_enemies.push_back(new Enemy(5, 5, 50, 5, 5, "images/etoile1.png", position, "spawn", "spawnMove" ,1, m_coefSpeed, 1, false, *player));
        enemy->upDateLastSpawnTime();
    }
}

Population* Population::getInstance()
  {
    if (NULL == _singleton)
      {
        std::cout << "population : creating singleton." << std::endl;
        _singleton =  new Population;
      }

    return _singleton;
  }

void Population::kill ()
  {
    if (NULL != _singleton)
      {
        delete _singleton;
        _singleton = NULL;
      }
  }

void Population::setPlayer(Player *externPlayer)
{
    player = externPlayer;
}

void Population::freeze()
{
    if(freezed != true)
    {
        timerFreeze.start();
        list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();lit++)
        {
            (*lit)->freeze();
        }

        Projectile_manager::getInstance()->freeze();
        m_coefSpeed /= 2;

        freezed = true;
    }
}

void Population::unfreeze()
{
    if(freezed == true)
    {
        list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();lit++)
        {
            (*lit)->unfreeze();
        }

        Projectile_manager::getInstance()->unfreeze();
        m_coefSpeed *= 2;

    }
    freezed = false;
}

bool Population::isFreezed()
{
    return freezed;
}
