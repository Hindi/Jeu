#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, RenderWindow &app,
                Player &player, image_manager &imageManager,Projectile_manager &projectile_manager, const char* name) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, app, player,
                  imageManager, projectile_manager),
            m_name(name)
{
    image = new Image();
    *image = imageManager.getImage(filepath);
    timer.start();
    timerMove.start();

    m_animated = new Animated;

    this->createAdd();
}

Boss::~Boss()
{
    delete m_animated;
    if (image!= NULL )
    {
        delete image;
    }
}

void Boss::createAdd()
{
    if(strcmp(m_name, "lily") == 0);
       // m_adds.push_back(new Adds(200, Vector2f(5, 5), "images/enemy.png", ));
}

