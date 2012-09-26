#include "population.h"

using namespace std;
using namespace sf;

Population::Population(RenderWindow &app, Projectile_manager &projectile_manager, Drop_manager &drop_manager, Player &player, image_manager &imageManager, Score_manager &scoreManager):
            m_app(app),
            m_player(player),
            m_imageManager(imageManager),
            m_projectile_manager(projectile_manager),
            m_drop_manager(drop_manager),
            m_scoreManager(scoreManager)
{

}


Population::~Population()
{
    if(this->haveEnnemyInProgress())
    {
        list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end(); lit++)
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
    m_projectile_manager.drawProjectile();//On les dessine

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

    m_projectile_manager.moveProjectile();

}

void Population::explode(Enemy *enemy)
{
    m_deadEnemies.push_back(enemy);

    Vector2f position;
    int score;
    score = enemy->getScoreExplosion();
    position.x = enemy->getPositionAxis(0);
    position.y = enemy->getPositionAxis(1);
    m_drop_manager.createDrop(score, position);
    int currentFrame = enemy->getAnimation()->GetCurrentFrame();
    Anim *m_anim = enemy->getAnimation()->GetAnim();
    Image *currentImage = (*m_anim)[currentFrame].Image;
    position.x += currentImage->GetWidth();
    m_scoreManager.addScore(score, position);
}

void Population::manageExplosion()
{
    unsigned int currentFrame;
    if(m_deadEnemies.size() > 0)
    {
        list<Enemy*>::iterator lit(m_deadEnemies.begin());
        for(; lit!=m_deadEnemies.end();lit++)
        {
            if((*lit)->getAnimationExplosion()->IsPaused())//Si l'animation est en pause
                (*lit)->getAnimationExplosion()->Play();//On relance l'animation
            currentFrame = (*lit)->getAnimationExplosion()->GetCurrentFrame();//On récupère le numéro de l'image qui est affichée
            (*lit)->getAnimationExplosion()->SetPosition((*lit)->getPositionAxis(0)-((*lit)->getExploWidth()/2), (*lit)->getPositionAxis(2)-((*lit)->getExploHeight()/2)+30);//On positionne l'animation sur l'ennemi qui a explose
            (*lit)->drawExplosion(); //On dessine l'explosion
            if(currentFrame == (*lit)->getAnimationExplosion()->GetAnim()->Size()-1)//Si l'image actuelle correspond à la dernière image de l'animation
            {
                lit = m_deadEnemies.erase(lit);//On détruit l'objet ennemi
            }
        }
    }

}

bool Population::haveEnnemyInProgress()
{
    if(m_enemies.size() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Population::freeze()
{
    list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();lit++)
        {
            (*lit)->pauseTimer();
        }
}

void Population::unFreeze()
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
    m_enemies.push_back(new Enemy(10, 10, 100, 5, 5, "images/enemy.png", position, "ship", move, 1, 40, 1, m_app, m_player, m_imageManager, m_projectile_manager, spawner));
}

void Population::createFlyingSaucer(Vector2f position, char* move, bool spawner)
{
    //parameters : life, score, xSpeed, ySpeed, filepath for image, position, enemy type, move type, move value, coefspeed, firerate, render window,player object, image manager, projectile manager
    m_enemies.push_back(new Enemy(30, 10, 500, 0, 0, "images/enemy2.png", position, "flyingSaucer", move, 1, 20, 2, m_app, m_player, m_imageManager, m_projectile_manager, spawner));
}

void Population::createBoss(Vector2f position, char* move, char* name)
{
    m_enemies.push_back(new Boss(500, 10, 10000, 5, 5, name, position, "boss", move, 1, 20, 2, m_app, m_player, m_imageManager, m_projectile_manager, name));
}

void Population::manage()
{
    this->checkPopulation();
    this->manageExplosion();
    this->drawPopulation();
}

bool Population::haveSpawnInProgress()
{
    if(m_spawn.size() >> 0)
        return true;
    else
        return false;
}

void Population::spawn(Enemy *enemy)
{
    if(enemy->isSpawner() && (enemy->getSpawnTime() - enemy->getLastSpawnTime() > enemy->getSpawnRate()))
    {
        Vector2f position = enemy->getPosition();
        m_enemies.push_back(new Spawn(5, 5, 50, 5, 5, "images/etoile1.png", position, "spawn", 1, 10, 1, m_app, m_player, m_imageManager, m_projectile_manager));
        enemy->upDateLastSpawnTime();
    }
}
