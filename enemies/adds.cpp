#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f relativePosition,
            const char* type, const char* moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, relativePosition, type, moveMethod, moveValue, coefSpeed, firerate, spawner, player, player2, allowTeleport),
            m_maxLife(life),
            relativePosition(relativePosition)
{

}

Adds::~Adds()
{

}


void Adds::teleport()
{
    teleporting = false;
    teleportTimer.reinitialize();
    teleportFrame = 0;
}

Vector2f Adds::getRelativePosition()
{
    return relativePosition;
}

void Adds::horizontalMove(int speed)
{
    m_position.x += speed;
    m_animated->SetPosition(m_position);
}

IntRect Adds::getBoundingBox()
{
    IntRect boundingBox;
    boundingBox.Left = m_position.x+20;
    boundingBox.Right = boundingBox.Left + image->GetWidth()/m_anim.Size()-40;
    boundingBox.Top = m_position.y;
    boundingBox.Bottom = boundingBox.Top + image->GetHeight();

    return boundingBox;
}
