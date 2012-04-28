#include "population.h"

using namespace std;
using namespace sf;

Population::Population(RenderWindow &app): m_app(app)
{

}


Population::~Population()
{
    if(this->haveEnnemyInProgress())
    {
        list<Enemy*>::const_iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end(); lit++)
        {
            delete *lit;
        }
    }
}

void Population::createEnemy(int score,int xSpeed, int ySpeed, const string &filepath, Vector2f position, RenderWindow &app, IntRect subRect)
{
    m_enemies.push_back(new Enemy(1, score, xSpeed, ySpeed, filepath, position, app, subRect));
}

void Population::drawPopulation()
{
    if(this->haveEnnemyInProgress())
    {
        list<Enemy*>::const_iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end(); lit++)
        {
            m_app.Draw(*(*lit)->getSprite());
        }
    }
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
        list<Enemy*>::iterator lit(m_enemies.begin());
        for(; lit!=m_enemies.end();)
        {
            if((*lit)->isDead())
            {
                lit = m_enemies.erase(lit);
            }
            else
            {
                lit++;
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
