#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, RenderWindow &app,
                Player &player, image_manager &imageManager,Projectile_manager &projectile_manager) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, app, player,
                  imageManager, projectile_manager)
{

}

Boss::~Boss()
{

}
