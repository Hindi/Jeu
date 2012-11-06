#include "boss.h"

using namespace std;
using namespace sf;

Boss::Boss(int life, int scoreHit, int scoreExplosion, int xSpeed, int ySpeed, const string &filepath, Vector2f position, char* type, char* moveMethod, int moveValue, const int coefSpeed, const int firerate, std::tr1::shared_ptr<Player> player,
           std::tr1::shared_ptr<Player> player2, bool allowTeleport) :
            Enemy(life, scoreHit, scoreExplosion, xSpeed, ySpeed, filepath, position, type, moveMethod, moveValue, coefSpeed, firerate, false, player, player2, allowTeleport)
{

}

Boss::~Boss()
{
    delete m_name;
}

void Boss::draw()
{
    if(teleporting)
    {
        if(teleportFrame % 2 == 1)
            app.Draw(*m_animated);
        teleportFrame++;
    }
    else
        app.Draw(*m_animated);
}


Vector2f Boss::getPosition()
{
    return m_position;
}

void Boss::setTeleporting(bool state)
{
    teleporting = state;
}

