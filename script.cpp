#include "script.h"

using namespace std;
using namespace sf;

Script::Script(short const id):
            id(id)
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
{/*
    while(1)
    {
        niveau1();
        timer.sleep(1000);
    }*/
}

void Script::niveau1()
{
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

}
