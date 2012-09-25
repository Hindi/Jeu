#include "script.h"

using namespace std;
using namespace sf;

Script::Script(int id, std::string msg, image_manager &imageManager, Player &player, Projectile_manager &projectile_manager, Population &population):
            id(id),
            msg(msg),
            m_imageManager(imageManager),
            m_player(player),
            m_projectileManager(projectile_manager),
            m_population(population)
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
    niveau1();
}

void Script::niveau1()
{
    //Variables enemy :
    Vector2f positionEnemy(50, 50);

    m_population.createShip(positionEnemy, "roundtrip",true);/*
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
