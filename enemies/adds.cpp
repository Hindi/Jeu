#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position,
            char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, spawner, player, player2),
            m_maxLife(5)
{

}

Adds::~Adds()
{
    delete image;
    delete m_animated;
}


Sprite* Adds::getSprite()
{
    return &sprite;
}
