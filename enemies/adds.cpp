#include "adds.h"

using namespace std;
using namespace sf;

Adds::Adds(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const std::string &filepath, sf::Vector2f relativePosition,
            const char* type, const char* moveMethod, int moveValue, const int coefSpeed, const int firerate, bool spawner, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2, bool allowTeleport):
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, relativePosition, type, moveMethod, moveValue, coefSpeed, firerate, spawner, player, player2, allowTeleport),
            m_maxLife(5),
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
    cout << speed << endl;
    m_animated->Move(Vector2f(0,speed*app.GetFrameTime()));
}
