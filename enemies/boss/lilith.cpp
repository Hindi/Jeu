#include "lilith.h"

using namespace std;
using namespace sf;

Lilith::Lilith(std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2) :
            Boss(10, 5, 10000, 5, 5, "images/lilith/corps.png", Vector2f(500, 500), "boss", "don't move", 1, 50, 2, player, player2, true),
            m_level(1),
            m_position(Vector2f(500,500))
{

}

Lilith::~Lilith()
{

}

void Lilith::addsMove()
{
    this->follow();
}

void Lilith::fire()
{
    this->VFire();
}

/*
void Lilith::follow()
{

}
*/
