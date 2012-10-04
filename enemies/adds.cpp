#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position,
            char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, sf::RenderWindow &app, Player &player,
            image_manager &imageManager, bool spawner):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, app, player,
                  imageManager, spawner),
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
