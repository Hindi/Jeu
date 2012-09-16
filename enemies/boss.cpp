#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, RenderWindow &app, Player &player, image_manager &imageManager, Projectile_manager &projectile_manager):
Unit(life, xSpeed,ySpeed, filepath, position, app, projectile_manager), m_player(player), direction("null"), lastShot(0), m_scoreHit(scoreHit), m_scoreExplosion(scoreExplosion), projectileSpeed(10), m_coefSpeed(coefSpeed), m_fireRate(firerate), savedTimerMove(0),
m_imageManager(imageManager), m_type(type), m_moveMethod(moveMethod), m_moveValue(moveValue)

{

}

Boss::~Boss()
{

}
