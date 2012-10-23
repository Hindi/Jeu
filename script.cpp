#include "script.h"

using namespace std;
using namespace sf;

Script::Script(short const id):
            id(id),
            finished(false),
            currentLevel(1)
{
    timer.start();
}

/*
*****************************************************************
Liste des ennemis disponibles :
- ship
- flyingSaucer

Liste des boss :
-Lily
*****************************************************************
*/

void Script::Run()
{
        cout << m_launchLevel << endl;
    switch(m_launchLevel)
    {
        case 1:
        {
            niveau1();
            break;
        }
        case 2:
        {
            niveau2();
            break;
        }
    }
}

void Script::niveau1()
{
    int i(0);
    while(i < 5)
    {
        finished = false;
        currentLevel = 1;
        //Variables enemy :
        Vector2f positionEnemy(50, 50);

        Population::getInstance()->createShip(positionEnemy, "roundtrip",true);/*
        positionEnemy.x +=100;
        m_population.createShip(positionEnemy, "roundtrip");
        positionEnemy.x +=100;
        m_population.createShip(positionEnemy, "roundtrip");
        positionEnemy.x +=100;
        m_population.createFlyingSaucer(positionEnemy, "roundtrip");
        positionEnemy.x +=100;
        m_population.createShip(positionEnemy, "roundtrip");
        positionEnemy.x +=100;
        m_population.createShip(positionEnemy, "roundtrip");
        positionEnemy.x +=100;

        //population.createFlyingSaucer(positionEnemy, player, m_imageManager);
        positionEnemy.x +=100;
        m_population.createShip(positionEnemy, "roundtrip");
        positionEnemy.x +=100;
        //population.createFlyingSaucer(positionEnemy, player, m_imageManager);
        m_population.createBoss(positionEnemy, "roundtrip", "lily");*/
        timer.sleep(10000);
        i++;
    }
    finished = true;
    timer.sleep(1000);
}

void Script::niveau2()
{
     finished = false;
    currentLevel = 1;
    //Variables enemy :
    Vector2f positionEnemy(500, 50);

    Population::getInstance()->createShip(positionEnemy, "Down",true);
    timer.sleep(10000);
    finished = true;
}

bool Script::isFinished()
{
    if(finished)
        return true;
    else
        return false;
}

short Script::nextLevel()
{
    return currentLevel + 1;
}

void Script::setLaunchLevel(short launchLevel)
{
    m_launchLevel = launchLevel;
}
