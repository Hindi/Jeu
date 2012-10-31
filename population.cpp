#include "population.h"

using namespace std;
using namespace sf;

Population *Population::_singleton= NULL;

Population::Population(): killRate(1)
{
    m_coefSpeed = 30;
    Population* _singleton= NULL;
    killedEnemies = 0;
    timerCombo.start();
    combo = 1;
    maxCombo = 0;
}


Population::~Population()
{
    this->reset();
}

void Population::drawPopulation()
{
    if(this->haveEnnemyInProgress())
    {
        list<tr1::shared_ptr<Enemy> >::const_iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end(); lit++)//Si des ennemis sont en vie
        {
            (*lit)->draw();//On les dessine
        }
    }
    if(this->haveBossInProgress())
    {
        list<tr1::shared_ptr<Boss> >::const_iterator li(m_boss.begin());
        for(; li!= m_boss.end(); li++)
        {
            (*li)->draw();
        }
    }
    Projectile_manager::getInstance()->drawProjectile();//On les dessine

}

list<tr1::shared_ptr<Enemy> >* Population::getPopulation()
{
    //Retourne la liste des ennemis
    return &m_enemies;
}

void Population::checkPopulation()
{
    if(this->haveEnnemyInProgress())
    {
        //On check les ennemis
        list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
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
                    if( strcmp((*lit)->getType(), "spawn") == 0 )
                        (*lit)->fireFocus();
                    if(strcmp((*lit)->getType(), "flyingSaucer") == 0)
                        (*lit)->fireCircle();
                }
                lit++;
            }
        }
    }

    if(this->haveBossInProgress())
    {
        list<tr1::shared_ptr<Boss> >::const_iterator li(m_boss.begin());
        for(; li!= m_boss.end(); li++)
        {
            (*li)->move();
            (*li)->addsMove();
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

void Population::explode(std::tr1::shared_ptr<Enemy> enemy)
{
    m_deadEnemies.push_back(enemy);

    Vector2f position;
    int score = enemy->getScoreExplosion();
    position.x = enemy->getPositionAxis(0);
    position.y = enemy->getPositionAxis(1);
    Drop_manager::getInstance()->createDrop(score, position);
    int currentFrame = enemy->getAnimation()->GetCurrentFrame();
    Anim *m_anim = enemy->getAnimation()->GetAnim();
    Image *currentImage = (*m_anim)[currentFrame].Image;
    position.x += currentImage->GetWidth();
    Score_manager::getInstance()->addScore(score, position);

    killedEnemies++;
    if(timerCombo.getTime() <= killRate)
    {
        combo++;
        if(combo > maxCombo)
            maxCombo = combo;
    }
    else
        combo = 1;
    timerCombo.reinitialize();

}

void Population::manageExplosion()
{
    if(!m_deadEnemies.empty())
    {
        short currentFrame;
        list<tr1::shared_ptr<Enemy> >::iterator lit(m_deadEnemies.begin());
        for(; lit!=m_deadEnemies.end();lit++)
        {
            //Si l'animation est en pause
            if((*lit)->getAnimationExplosion()->IsPaused())
                (*lit)->getAnimationExplosion()->Play();//On relance l'animation
            //On récupère le numéro de l'image qui est affichée
            currentFrame = (*lit)->getAnimationExplosion()->GetCurrentFrame();
            Vector2f position(0,0);
            position.x = (*lit)->getPositionAxis(0) + (*lit)->getSize().x/2 - ((*lit)->getExploWidth()/2);
            position.y = (*lit)->getPositionAxis(1) + (*lit)->getSize().y/2 - ((*lit)->getExploHeight()/2);
            //On positionne l'animation sur l'ennemi qui a explose
            (*lit)->getAnimationExplosion()->SetPosition(position);
             //On dessine l'explosion
            (*lit)->drawExplosion();
            //Si l'image actuelle correspond à la dernière image de l'animation
            if(currentFrame == (*lit)->getAnimationExplosion()->GetAnim()->Size()-1)
            {
                lit = m_deadEnemies.erase(lit);//On détruit l'objet ennemi
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
    list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
    for(; lit!=m_enemies.end();lit++)
    {
        (*lit)->pauseTimer();
    }
}

void Population::unStop()
{
    list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
    for(; lit!=m_enemies.end();lit++)
    {
        (*lit)->startTimer();
    }
}

void Population::createShip(Vector2f position, char* move, bool spawner)
{
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(10, 10, 100, 5, 5, "images/enemy.png", position, "ship", move, 1, m_coefSpeed, 1, spawner, player, player2));
    m_enemies.push_back(a);
}

void Population::createFlyingSaucer(Vector2f position, char* move, bool spawner)
{
    m_coefSpeed = 20;
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(30, 10, 500, 0, 0, "images/enemy2.png", position, "flyingSaucer", move, 1, m_coefSpeed, 2, spawner, player, player2));
    m_enemies.push_back(a);
}

void Population::spawn(std::tr1::shared_ptr<Enemy> enemy)
{
    if(enemy->isSpawner() && (enemy->getSpawnTime() - enemy->getLastSpawnTime() > enemy->getSpawnRate()))
    {
        Vector2f position = enemy->getPosition();
        m_coefSpeed = 10;
        tr1::shared_ptr<Enemy> a(new Enemy(5, 5, 50, 5, 5, "images/enemySpawn1.png", position, "spawn", "spawnMove" ,1, m_coefSpeed, 1, false, player, player2));
        m_enemies.push_back(a);
        enemy->upDateLastSpawnTime();
    }
}

void Population::createLilith()
{
    string filepath = "images/enemy2.png";
    tr1::shared_ptr<Boss> a(new Lilith(player, player2));
    m_boss.push_back(a);
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

void Population::setPlayer(std::tr1::shared_ptr<Player> externPlayer, std::tr1::shared_ptr<Player> externPlayer2)
{
    player = externPlayer;
    player2 = externPlayer2;
}

void Population::freeze()
{
    if(freezed != true)
    {
        timerFreeze.start();
        list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
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
        list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
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

void Population::reset()
{
    m_enemies.clear();
    m_deadEnemies.clear();
    m_spawns.clear();
}

int Population::getKilledEnemies()
{
    return killedEnemies;
}

unsigned short Population::getCombo()
{
    return maxCombo;
}

void Population::killThemAll()
{
    list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
    for(; lit!=m_enemies.end();)
    {
        this->explode(*lit);
        lit = m_enemies.erase(lit);
    }
}

bool Population::haveBossInProgress()
{
    if(m_boss.empty())
    {
        return false;
    }
    else
        return true;
}
