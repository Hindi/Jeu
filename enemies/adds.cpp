#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f relativePosition,
            const char* type, const char* moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport, tr1::shared_ptr<Boss> boss):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, relativePosition, type, moveMethod, moveValue, coefSpeed, firerate, spawner, player, player2, allowTeleport),
            m_maxLife(5),
            m_boss(boss),
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

void Adds::follow()
{
    m_animated->SetPosition(Vector2f(m_boss->getPosition().x + relativePosition.x, m_boss->getPosition().y + relativePosition.y));
    m_position = (Vector2f(m_boss->getPosition().x + relativePosition.x, m_boss->getPosition().y + relativePosition.y));
}
