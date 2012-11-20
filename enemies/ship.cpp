#include "ship.h"

using namespace std;
using namespace sf;

Ship::Ship(Vector2f position, const std::string &move, std::tr1::shared_ptr<Player> player, std::tr1::shared_ptr<Player> player2):
            Enemy(10, 10, 100, 5, 5, "images/enemy.png", position, "ship", move, 1, m_coefSpeed, 1, false, player, player2, false)
{

}

Ship::~Ship()
{

}

void Ship::fire()
{
    this->fireFocus();
}
