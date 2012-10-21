#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, const char* name, std::tr1::shared_ptr<Player> player) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player),
            m_name(name)
{
    image = new Image();
    *image = image_manager::getInstance()->getImage(filepath);
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
    delete m_name;
}

void Boss::createAdd()
{
    if(strcmp(m_name, "lily") == 0);
       // m_adds.push_back(new Adds(200, Vector2f(5, 5), "images/enemy.png", ));
}

