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
    bossSpawned = false;

    boomBuffer = sound_manager::getInstance()->getBuffer("son/boom.ogg");
    boomSound.SetBuffer(boomBuffer);
    boomSound.SetLoop(false);
    boomSound.SetPitch(1.f);
    boomSound.SetVolume(50.f);

    boom2Buffer = sound_manager::getInstance()->getBuffer("son/boom2.ogg");
    boom2Sound.SetBuffer(boom2Buffer);
    boom2Sound.SetLoop(false);
    boom2Sound.SetPitch(1.f);
    boom2Sound.SetVolume(50.f);
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
        if(bossSpawned && currentBoss->isDead())
        {
            cout << "huk" << endl;
            this->killThemAll();
            bossSpawned = false;
        }
        else
        {
                //On check les ennemis
            list<tr1::shared_ptr<Enemy> >::iterator lit(m_enemies.begin());
            for(; lit!=m_enemies.end();)
            {
                if((*lit)->isDead())
                {
                    this->explode(*lit);
                    if(rand() % 2 > 0)
                        boomSound.Play();
                    else
                        boom2Sound.Play();

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
                        if(strcmp((*lit)->getType(), "boss") == 0)
                            (*lit)->fire();
                        if(strcmp((*lit)->getType(), "spawner") == 0)
                            (*lit)->fireSpawner();
                    }
                    if((*lit)->canTeleport())
                    {
                        (*lit)->setTeleporting(true);
                        if((*lit)->readyToTeleport())
                        {
                            (*lit)->teleport();
                        }
                    }
                    lit++;
                }
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
        for(; lit!=m_deadEnemies.end();)
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
            else
                lit++;
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

void Population::createShip(Vector2f position, const std::string &move)
{
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(10, 10, 100, 3, 3, "images/enemy.png", position, "ship", move, 1, m_coefSpeed, 1, false, player, player2, false));
    m_enemies.push_back(a);
}

void Population::createShip2(const std::string &move)
{
    Vector2f randPosition;
    randPosition.x = rand() % 768 + 10;
    randPosition.y = -100;
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(1, 15, 100, 7, 7, "images/enemy.png", randPosition, "ship", move, 1, m_coefSpeed, 1, false, player, player2, false));
    m_enemies.push_back(a);
}

void Population::createFlyingSaucer(Vector2f position, const std::string &move)
{
    m_coefSpeed = 20;
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(60, 10, 500, 1, 1, "images/flyingSaucer1.png", position, "flyingSaucer", move, 1, m_coefSpeed, 2, false, player, player2, false));
    m_enemies.push_back(a);
}

void Population::createFlyingSaucer2(Vector2f position, const std::string &move)
{
    m_coefSpeed = 20;
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(30, 10, 500, 2, 2, "images/flyingSaucer2.png", position, "flyingSaucer", move, 1, m_coefSpeed, 1, false, player, player2, false));
    m_enemies.push_back(a);
}

void Population::createAdd(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position, sf::Vector2f absolutePosition, const char* type, const char* moveMethod, int moveValue,
              const int coefSpeed, const int firerate,bool spawner, std::tr1::shared_ptr<Player> externPlayer, std::tr1::shared_ptr<Player> externPlayer2)
{
    tr1::shared_ptr<Adds> add(new Adds(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, absolutePosition, type, moveMethod, moveValue, coefSpeed, firerate, spawner, externPlayer, externPlayer2, false));
    m_enemies.push_front(add);
    currentBoss->pushAdd(add);
}

void Population::createSpawner(Vector2f position, const std::string &move)
{
    m_coefSpeed = 20;
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    tr1::shared_ptr<Enemy> a(new Enemy(30, 10, 500, 2, 2, "images/Spawner.png", position, "spawner", move, 1, m_coefSpeed, 2, true, player, player2, false));
    m_enemies.push_back(a);
}

void Population::spawn(std::tr1::shared_ptr<Enemy> enemy)
{
    if(enemy->isSpawner() && (enemy->getSpawnTime() - enemy->getLastSpawnTime() > enemy->getSpawnRate()))
    {
        Vector2f position = enemy->getPosition();
        position.x += 10;
        position.y += 40;
        m_coefSpeed = 10;
        tr1::shared_ptr<Enemy> a(new Enemy(5, 5, 50, 5, 5, "images/enemySpawn1.png", position, "spawn", "spawnMove" ,1, m_coefSpeed, 1, false, player, player2, false));
        m_enemies.push_back(a);
        enemy->upDateLastSpawnTime();
    }
}

void Population::createLilith()
{
    tr1::shared_ptr<Boss> lilith(new Lilith(player, player2));
    m_enemies.push_back(lilith);
    currentBoss = lilith;
    Vector2f position(130, 96);
    Vector2f absolutePosition(lilith->getPosition().x + position.x, lilith->getPosition().y + position.y);
    this->createAdd(50000, 0, 50, 5, 5, "images/lilith2.0/bouclier.png", position, absolutePosition, "add", "follow" ,1, m_coefSpeed, 1, false, player, player2);
    position.x +=65;
    this->createAdd(50000, 0, 50, 5, 5, "images/lilith2.0/bouclier2.png", position, absolutePosition, "add", "follow" ,1, m_coefSpeed, 1, false, player, player2);
    bossSpawned = true;
}

void Population::createOctopus()
{
    tr1::shared_ptr<Boss> octopus(new Octopus(player, player2));
    currentBoss = octopus;
    m_enemies.push_back(octopus);
    Vector2f position(-140, 90);
    Vector2f absolutePosition(octopus->getPosition().x + position.x, octopus->getPosition().y + position.y);
    for(int i=0; i < 15; i++)
    {
        this->createAdd(100, 5, 50, 5, 5, "images/octopus/Tentacule.png", position, absolutePosition, "add", "follow" ,1, m_coefSpeed, 1, false, player, player2);
        position.y += 30;
    }
    position.x = 350;
    position.y = 90;
    for(int i=0; i < 15; i++)
    {
        this->createAdd(100, 5, 50, 5, 5, "images/octopus/Tentacule.png", position, absolutePosition, "add", "follow" ,1, m_coefSpeed, 1, false, player, player2);
        position.y += 30;
    }
    bossSpawned = true;
}

void Population::manage()
{
    this->checkPopulation();
    this->manageExplosion();
    this->drawPopulation();
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
    //m_spawns.clear();
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
