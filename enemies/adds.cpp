#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f position,
            char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, spawner, player, player2),
            m_maxLife(5)
{
    m_animated = new Animated;
    m_anim.PushFrame(Frame(image, sf::Rect<int>(0, 0, image->GetWidth(), image->GetHeight()) ));
    m_animated->SetAnim(&m_anim);
    m_animated->Play();
    m_animated->SetPosition(position.x, position.y);
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

void Adds::follow(sf::Vector2f speed)
{
    m_animated->Move(speed);
}

void Adds::follow()
{

}
