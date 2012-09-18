#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, Vector2f speed, const string &filepath, Vector2f position, RenderWindow &app, Projectile_manager projectile_manager,
            Player &player, image_manager &imageManager):
            Unit(life, speed.x,speed.y, filepath, position, app, projectile_manager),
            m_scoreHit(20),
            m_scoreExplosion(500),
            projectileSpeed(10),
            m_coefSpeed(50),
            m_fireRate(1),
            m_player(player),
            m_imageManager(imageManager)
{

}

Adds::~Adds()
{

}
